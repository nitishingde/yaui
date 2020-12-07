#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include "yaui.h"

using namespace yaui;

TEST_CASE("Test yaui", "[yaui]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->pushScene(new Scene("Test yaui"));
    dir->run();
}

TEST_CASE("Test yaui Label", "[yaui][Label]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->disableStats();
    dir->setFPS(60);
    dir->pushScene(new Scene("Test yaui"));
    auto &registry = dir->getScene().getRegistry();
    auto labelEntity = entity::ViewFactory::produceLabel(
        registry,
        "Hello World!",
        "OpenSans-Regular.ttf",
        32,
        {255, 255, 255, 255},
        {255, 0, 0, 0},
        {0, 10 , 10, 0},
        {5, 5 , 5, 5},
        {127, 127, 127, 127},
        40,
        30
    );
    auto &actionItems = registry.emplace<component::ActionItems>(labelEntity);
    actionItems.actions.emplace_back(Action(
        "DiscoBackground",
        1.f,
        [](entity::Registry &registry, const entity::Entity &entity, float delay, uint64 counter) {
            auto [texture2D, textureTransformationJobs] = registry.get<component::Texture2D, component::TextureTransformationJobs>(entity);
            texture2D.backgroundColour.g = (texture2D.backgroundColour.g+32)%256;
            texture2D.backgroundColour.b = (texture2D.backgroundColour.b+32)%256;
            texture2D.backgroundColour.a = (texture2D.backgroundColour.a+32)%256;
            textureTransformationJobs.trigger();
            spdlog::info("DiscoBackground (Delay = {:.2f}, Counter = {})", delay, counter);
            return true;
        }
    ));
    dir->run();
}

TEST_CASE("Test yaui Button", "[yaui][Button]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->enableStats();
    dir->setFPS(60);
    dir->pushScene(new Scene("Test yaui"));
    auto &registry = dir->getScene().getRegistry();
    auto entity = entity::ViewFactory::produceButton(
        registry,
        "Hello World!",
        "OpenSans-Regular.ttf",
        32,
        {255, 255, 255, 255},
        {255, 0, 0, 127},
        {0, 10 , 10, 0},
        {5, 5 , 5, 5},
        {127, 127, 127, 127},
        40,
        30
    );
    auto &mouseEventListener = registry.get<component::MouseEventListener>(entity);
    mouseEventListener.onClickListeners.emplace_back(
        [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
            auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
            backgroundColour.g = (backgroundColour.g+64)%256;
            registry.get<component::TextureTransformationJobs>(entity).trigger();
            return true;
        }
    );
    mouseEventListener.onHoverEnterListeners.emplace_back(
        [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
            auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
            backgroundColour.b = 255;
            registry.get<component::TextureTransformationJobs>(entity).trigger();
            return true;
        }
    );
    mouseEventListener.onHoverLeaveListeners.emplace_back(
        [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
            auto &backgroundColour = registry.get<component::Texture2D>(entity).backgroundColour;
            backgroundColour.b = 0;
            registry.get<component::TextureTransformationJobs>(entity).trigger();
            return true;
        }
    );
    dir->run();
}

TEST_CASE("Test yaui TextField", "[yaui][TextField]") {
    Director *dir = Director::getInstance();
    REQUIRE(dir != nullptr);
    dir->enableStats();
    dir->setFPS(60);
    dir->pushScene(new Scene("Test yaui"));
    auto &registry = dir->getScene().getRegistry();
    entity::ViewFactory::produceTextField(
        registry,
        "Hello!",
        "OpenSans-Regular.ttf",
        32,
        {0, 255, 0, 255},
        {255, 255, 255, 127},
        {0, 10, 10, 0},
        {5, 5, 5, 5},
        {127, 127, 127, 127},
        40,
        30,
        {256, 64}
    );
    dir->run();
}

TEST_CASE("Test calculator application", "[yaui][app]") {
    struct CalculatorModel {
        double result = 0;
        String _operator;
        entity::Entity resultDisplayLabel = entity::null;
    };

    auto dir = Director::getInstance();
    dir->setFPS(60);
    dir->pushScene(new Scene("Calculator"));
    dir->setWindowBackgroundColour({64, 64, 64, 255});
    dir->setWindowSize(Size{512+40, 512+64+48});
    auto &scene = dir->getScene();
    auto &calculatorModel = scene.getRegistry().set<CalculatorModel>();

    auto resultDisplayLabel = entity::ViewBuilder::initiateBaseView(scene.getRegistry())
        .buildBoxModelComponent({0, 0, 0, 0}, {0, 0, 0, 0}, {0, 32, 32, 0})
        .buildTextureTransformationComponent(
            {
                TextureTransformationFactory::produceAddBackgroundColourTextureTransformation(),
                TextureTransformationFactory::produceAddLabelTextureTransformation()
            }
        )
        .buildTextComponent("0", "OpenSans-Regular.ttf", 32, {255, 255, 255, 255})
        .buildTexture2DComponent({127, 127, 127, 255})
        .buildTransformComponent({8, 8, 512+24, 64})
        .buildView();
    calculatorModel.resultDisplayLabel = resultDisplayLabel;

    int y = 80;
    for(auto &row: ArrayList<ArrayList<String>>{{"7", "8", "9", "+"}, {"4", "5", "6", "-"}, {"1", "2", "3", "*"}, {"0", ".", "=", "/"}}) {
        int x = 8;
        for(auto &digit: row) {
            auto onClick = [](yaui::entity::Registry &registry, const yaui::entity::Entity &entity, const yaui::Event &event) {
                auto &model = registry.ctx<CalculatorModel>();
                auto buttonText = registry.get<component::Text>(entity).value;

                if(event.type == EventType::SDL_MOUSEBUTTONDOWN);
                else if(event.type == EventType::SDL_TEXTINPUT and buttonText != event.text.text) return true;
                else if(event.type == EventType::SDL_KEYDOWN) return true;
                else if(event.type == EventType::SDL_KEYUP and event.key.keysym.sym != KeyCode::SDLK_KP_ENTER) return true;
                else if(event.type == EventType::SDL_KEYUP and event.key.keysym.sym == KeyCode::SDLK_KP_ENTER and buttonText != "=") return true;

                auto resultDisplayLabel = model.resultDisplayLabel;
                auto calculate = [](double operand1, const String &_operator, double operand2) {
                    if(_operator == "+") return operand1+operand2;
                    if(_operator == "-") return operand1-operand2;
                    if(_operator == "*") return operand1*operand2;
                    if(_operator == "/") return operand1/operand2;
                    return operand2;
                };
                if(buttonText == "+") {
                    model.result = calculate(
                        model.result,
                        model._operator,
                        std::atof(registry.get<component::Text>(resultDisplayLabel).value.c_str())
                    );
                    model._operator = "+";
                    registry.get<component::Text>(resultDisplayLabel).value = "0";
                } else if(buttonText == "-") {
                    model.result = calculate(
                        model.result,
                        model._operator,
                        std::atof(registry.get<component::Text>(resultDisplayLabel).value.c_str())
                    );
                    model._operator = "-";
                    registry.get<component::Text>(resultDisplayLabel).value = "0";
                } else if(buttonText == "*") {
                    model.result = calculate(
                        model.result,
                        model._operator,
                        std::atof(registry.get<component::Text>(resultDisplayLabel).value.c_str())
                    );
                    model._operator = "*";
                    registry.get<component::Text>(resultDisplayLabel).value = "0";
                } else if(buttonText == "/") {
                    model.result = calculate(
                        model.result,
                        model._operator,
                        std::atof(registry.get<component::Text>(resultDisplayLabel).value.c_str())
                    );
                    model._operator = "/";
                    registry.get<component::Text>(resultDisplayLabel).value = "0";
                } else if(buttonText == ".") {
                    if(auto &displayText = registry.get<component::Text>(resultDisplayLabel); displayText.value.find_first_of(".", 0) == String::npos) {
                        displayText.value += ".";
                    }
                } else if (buttonText == "=" or event.type == EventType::SDL_KEYUP and event.key.keysym.sym == KeyCode::SDLK_KP_ENTER) {
                    model.result = calculate(
                        model.result,
                        model._operator,
                        std::atof(registry.get<component::Text>(resultDisplayLabel).value.c_str())
                    );
                    registry.get<component::Text>(resultDisplayLabel).value = std::to_string(model.result);
                    model._operator = "=";
                } else {
                    if(auto &displayText = registry.get<component::Text>(resultDisplayLabel); displayText.value == "0") {
                        displayText.value = registry.get<component::Text>(entity).value;
                    } else {
                        displayText.value += registry.get<component::Text>(entity).value;
                    }
                }
                registry.get<component::TextureTransformationJobs>(resultDisplayLabel).trigger();
                return true;
            };
            entity::ViewBuilder::initiateBaseView(scene.getRegistry())
                .buildBoxModelComponent({0, 0, 0, 0}, {0, 0, 0, 0}, {0, 32, 0, 16})
                .buildTextureTransformationComponent(
                    {
                        TextureTransformationFactory::produceAddBackgroundColourTextureTransformation(),
                        TextureTransformationFactory::produceAddLabelTextureTransformation()
                    }
                )
                .buildTextComponent(digit, "OpenSans-Regular.ttf", 64, {255, 255, 255, 255})
                .emplaceBackListenersToMouseEventListenerComponent(onClick)
                .buildTransformComponent({x, y, 128, 128})
                .buildTexture2DComponent({32, 32, 32, 255}, 0)
                .buildTextInputEventListener(true)
                .emplaceBackListenersToTextInputEventListener(onClick, nullptr)
                .buildKeyboardEventListenerComponent(true)
                .emplaceBackListenersToKeyboardEventListenerComponent(nullptr, onClick)
                .buildView();
            x += 136;
        }
        y += 136;
    }
    dir->run();
}
