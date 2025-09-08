file(GLOB_RECURSE CARD_BATTLE_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(retronomicon-card-battle ${CARD_BATTLE_SRC})

target_include_directories(retronomicon-card-battle
    PUBLIC
        ${RETRO_CARD_BATTLE_DIR}/include
        ${RETRO_CARD_BATTLE_DIR}/external/json/include
        ${RETRO_INCLUDE_DIR}   # retronomicon's include directory
)

target_link_libraries(retronomicon-conversation
    PUBLIC
        retronomicon          # link the base engine
        nlohmann_json::nlohmann_json
)
