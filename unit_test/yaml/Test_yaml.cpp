#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch2/catch.hpp"
#include "yaml-cpp/yaml.h"

TEST_CASE("Initialization of yaml", "[init]") {
    auto node = YAML::LoadFile("test.yaml");
    if(node["parsing_support"].as<bool>()) {
        std::cout<<node["name"].as<std::string>()<<std::endl;
        auto vector = node["vector"].as<std::vector<int>>();
        for(auto it: vector) std::cout<<it<<' ';
        std::cout<<std::endl;
    }
}