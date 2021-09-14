#include "tilemap.hpp"

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <unordered_map>

#include "picojson.h"
#include "renderer.hpp"

namespace htn {

Tilemap::Tilemap(const std::string& filename) {
    using namespace picojson;

    std::ifstream fs{filename};

    value js_root_value;
    std::string err;

    parse(js_root_value, std::istream_iterator<char>{fs}, std::istream_iterator<char>{}, &err);

    if (!err.empty()) {
        throw std::runtime_error{std::move(err)};
    }

    auto last_slash_pos = filename.rfind('/');

    std::string base_path;

    if (last_slash_pos != std::string::npos) {
        base_path = filename.substr(0, last_slash_pos + 1);
    }

    auto& js_root = js_root_value.get<object>();

    m_tile_size.x = static_cast<int>(js_root.at("tilewidth").get<double>());
    m_tile_size.y = static_cast<int>(js_root.at("tileheight").get<double>());

    std::unordered_map<int, std::string> object_gid_to_type;

    auto& js_tilesets = js_root.at("tilesets").get<array>();

    m_tilesets.reserve(js_tilesets.size());

    for (auto& js_tileset_value : js_tilesets) {
        auto& js_tileset = js_tileset_value.get<object>();

        auto first_gid = static_cast<int>(js_tileset.at("firstgid").get<double>());

        auto js_tiles_found = js_tileset.find("tiles");

        if (js_tiles_found != js_tileset.end()) {
            for (auto& js_tile_value : js_tiles_found->second.get<array>()) {
                auto& js_tile = js_tile_value.get<object>();

                object_gid_to_type.try_emplace(
                    first_gid + static_cast<int>(js_tile.at("id").get<double>()),
                    js_tile.at("type").get<std::string>());
            }

            continue;
        }

        Tileset tileset;

        tileset.first_id = first_gid;
        tileset.image = std::make_shared<Image>(
            (base_path + js_tileset.at("image").get<std::string>()).c_str());

        m_tilesets.emplace_back(std::move(tileset));
    }

    auto& js_layers = js_root.at("layers").get<array>();

    for (auto& js_layer_value : js_layers) {
        auto& js_layer = js_layer_value.get<object>();

        if (js_layer.at("type").get<std::string>() == "tilelayer") {
            TileLayer tile_layer;

            tile_layer.name = js_layer.at("name").get<std::string>();

            tile_layer.width = static_cast<int>(js_layer.at("width").get<double>());
            tile_layer.height = static_cast<int>(js_layer.at("height").get<double>());

            auto& js_data = js_layer.at("data").get<array>();

            tile_layer.data.reserve(js_data.size());

            for (auto& js_data_elem_value : js_data) {
                tile_layer.data.emplace_back(static_cast<int>(js_data_elem_value.get<double>()));
            }

            m_tile_layers.emplace_back(std::move(tile_layer));
        } else {
            ObjectLayer object_layer;

            object_layer.name = js_layer.at("name").get<std::string>();

            auto& js_objects = js_layer.at("objects").get<array>();

            object_layer.objects.reserve(js_objects.size());

            for (auto& js_object_value : js_objects) {
                auto& js_object = js_object_value.get<object>();

                auto found_gid = js_object.find("gid");

                Object object;

                object.id = static_cast<int>(js_object.at("id").get<double>());

                object.name = js_object.at("name").get<std::string>();

                object.rect.x = static_cast<float>(js_object.at("x").get<double>());
                object.rect.y = static_cast<float>(js_object.at("y").get<double>());
                object.rect.w = static_cast<float>(js_object.at("width").get<double>());
                object.rect.h = static_cast<float>(js_object.at("height").get<double>());

                object.rotation = static_cast<float>(js_object.at("rotation").get<double>());

                if (found_gid != js_object.end()) {
                    object.type =
                        object_gid_to_type[static_cast<int>(found_gid->second.get<double>())];

                    object.rect.y -= object.rect.h;
                } else {
                    object.type = js_object.at("type").get<std::string>();
                }

                object_layer.objects.emplace_back(std::move(object));
            }

            m_object_layers.emplace_back(std::move(object_layer));
        }
    }
}

void Tilemap::render(Renderer& r, Vec2f camera_offset) const {
    for (auto& tile_layer : m_tile_layers) {
        std::shared_ptr<Image> image;

        for (int y = 0; y < tile_layer.height; ++y) {
            for (int x = 0; x < tile_layer.width; ++x) {
                int id = tile_layer.data[x + y * tile_layer.width];

                if (id == 0) {
                    continue;
                }

                for (auto& tileset : m_tilesets) {
                    if (id >= tileset.first_id && image != tileset.image) {
                        image = tileset.image;
                    }
                }

                if (!image) {
                    continue;
                }

                id -= 1;

                int cols = image->width() / m_tile_size.x;

                int tx = id % cols;
                int ty = id / cols;

                r.blit(*image,
                       {x * m_tile_size.x - camera_offset.x, y * m_tile_size.y - camera_offset.y},
                       {tx * m_tile_size.x, ty * m_tile_size.y, m_tile_size.x, m_tile_size.y});
            }
        }
    }
}

const std::vector<Tilemap::ObjectLayer>& Tilemap::object_layers() const { return m_object_layers; }

}  // namespace htn
