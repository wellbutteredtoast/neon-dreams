#ifndef ITEM_VALIDATE_HPP
#define ITEM_VALIDATE_HPP

#include <nlohmann/json.hpp>
#include <fstream>

static const std::string item_key = "0xA1D4FC33";
static const std::string npc_key = "0x08DCA670";

static std::string _xor(const std::string& data, const std::string& key) {
    std::string result;
    result.reserve(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        result.push_back(data[i] ^ key[i % key.size()]);
    }
    return result;
}

// This does not check if the actual data is valid, only if the JSON
// schema is being followed by the output -- post once XOR is done.
/*****************************************************************************/
bool is_secure_item_json_valid(const std::string absolute_path) {
    /**
     * Item JSON Scheme
     * 
     * {
     *   "item_id":
     *   {
     *     "name": "",
     *     "desc": "",
     *     "type": "",
     *     "attributes" : []
     *   }
     * }
     */

    if (!std::filesystem::exists(absolute_path) || \
        std::filesystem::path(absolute_path).extension() != ".item") {
            return false;
    }

    std::ifstream file(absolute_path, std::ios::binary);
    if (!file.is_open()) return false;

    std::string encrypted_data((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

    std::string plaintext_data = _xor(encrypted_data, item_key);

    // Cobbled together system for figuring out the schema
    nlohmann::json json_data;
    try {
        json_data = nlohmann::json::parse(plaintext_data);
    } catch (nlohmann::json::parse_error&) {
        return false;  // Not valid JSON
    }

    // Step 5: Validate the schema
    if (!json_data.is_object()) return false;

    for (auto& [item_id, item_info] : json_data.items()) {
        if (!item_info.is_object()) return false;

        const std::vector<std::string> required_fields = { "name", "desc", \
                                                        "type", "attributes" };
        for (const auto& field : required_fields) {
            if (!item_info.contains(field) || !item_info[field].is_string()) {
                return false;
            }
        }
    }

    return true;
}

/*****************************************************************************/
// Unfinished stub func -- implement once the npc editor and packager are ready
bool is_secure_npc_json_valid(const std::string absolute_path) {
    if (!std::filesystem::exists(absolute_path) || \
        std::filesystem::path(absolute_path).extension() != ".npc") {
            return false;
    }

    std::ifstream file(absolute_path, std::ios::binary);
    if (!file.is_open()) return false;

    std::string encrypted_data((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

    std::string plaintext_data = _xor(encrypted_data, npc_key);
}

#endif // item_validate.hpp