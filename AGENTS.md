# Repository Guidelines

## Project Structure & Module Organization

`retronomicon-card-battle` is a C++17 gameplay module layered on the base `retronomicon` engine. Public headers are under `include/retronomicon/lib/card-battle/`. Implementations are under `src/lib/card-battle/`, currently split into `battle/` state and scene logic plus `data/` card, deck, hand, player, and database models. The module is normally built from the workspace root, where `retronomicon` and `nlohmann_json` are already available.

## Build, Test, and Development Commands

- From the workspace root, run `./build-sandbox.sh` to configure, build, and copy shared assets.
- Use `cmake -S . -B build` and `cmake --build build` from the workspace root for manual builds.
- Run `./play.sh` from the workspace root to exercise the sandbox integration.

There is no module-local standalone test runner yet; verify changes through the workspace build and sandbox.

## Coding Style & Naming Conventions

Use C++17. Follow existing lowercase snake case filenames such as `battle_state_machine.cpp` and `card_database.h`. Types use PascalCase (`BattleContext`, `CardDatabase`), while methods and variables use lower camelCase (`loadFromFile`, `discardPile`). Keep public contracts in `include/` and implementation details in `src/`.

## Testing Guidelines

When adding tests, prefer Catch2 tests integrated through the workspace or base engine test setup. Name files `test_*.cpp` and write targeted cases for deck loading, card creation, battle transitions, and invalid JSON data. Until tests exist here, include sandbox verification steps in PRs.

## Commit & Pull Request Guidelines

Use concise, imperative commit messages, for example `fix deck loading` or `add battle state transition`. PRs should describe gameplay behavior changes, mention any required updates to `asset/card/cards.json` or `asset/deck/deck.json`, and include build or sandbox run results.
