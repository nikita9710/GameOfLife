#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "Rules/ReplicatorRules.h"
#include "Rules/SeedsRules.h"

TEST_CASE("Conway Rules Next states") {
    auto rules = gol::rules::ConwayRules();

    REQUIRE_FALSE(rules.IsNextStateStable(0));
    REQUIRE_FALSE(rules.IsNextStateStable(1));
    REQUIRE(rules.IsNextStateStable(2));
    REQUIRE(rules.IsNextStateStable(3));
    REQUIRE_FALSE(rules.IsNextStateStable(4));
    REQUIRE_FALSE(rules.IsNextStateStable(5));
    REQUIRE_FALSE(rules.IsNextStateStable(6));
    REQUIRE_FALSE(rules.IsNextStateStable(7));
    REQUIRE_FALSE(rules.IsNextStateStable(8));

    REQUIRE_FALSE(rules.IsNextStateBirth(0));
    REQUIRE_FALSE(rules.IsNextStateBirth(1));
    REQUIRE_FALSE(rules.IsNextStateBirth(2));
    REQUIRE(rules.IsNextStateBirth(3));
    REQUIRE_FALSE(rules.IsNextStateBirth(4));
    REQUIRE_FALSE(rules.IsNextStateBirth(5));
    REQUIRE_FALSE(rules.IsNextStateBirth(6));
    REQUIRE_FALSE(rules.IsNextStateBirth(7));
    REQUIRE_FALSE(rules.IsNextStateBirth(8));
}

TEST_CASE("Seeds Rules Next states") {
    auto rules = gol::rules::SeedsRules();

    REQUIRE_FALSE(rules.IsNextStateStable(0));
    REQUIRE_FALSE(rules.IsNextStateStable(1));
    REQUIRE_FALSE(rules.IsNextStateStable(2));
    REQUIRE_FALSE(rules.IsNextStateStable(3));
    REQUIRE_FALSE(rules.IsNextStateStable(4));
    REQUIRE_FALSE(rules.IsNextStateStable(5));
    REQUIRE_FALSE(rules.IsNextStateStable(6));
    REQUIRE_FALSE(rules.IsNextStateStable(7));
    REQUIRE_FALSE(rules.IsNextStateStable(8));

    REQUIRE_FALSE(rules.IsNextStateBirth(0));
    REQUIRE_FALSE(rules.IsNextStateBirth(1));
    REQUIRE(rules.IsNextStateBirth(2));
    REQUIRE_FALSE(rules.IsNextStateBirth(3));
    REQUIRE_FALSE(rules.IsNextStateBirth(4));
    REQUIRE_FALSE(rules.IsNextStateBirth(5));
    REQUIRE_FALSE(rules.IsNextStateBirth(6));
    REQUIRE_FALSE(rules.IsNextStateBirth(7));
    REQUIRE_FALSE(rules.IsNextStateBirth(8));
}

TEST_CASE("Replicator Rules Next states") {
    auto rules = gol::rules::ReplicatorRules();

    REQUIRE_FALSE(rules.IsNextStateStable(0));
    REQUIRE(rules.IsNextStateStable(1));
    REQUIRE_FALSE(rules.IsNextStateStable(2));
    REQUIRE(rules.IsNextStateStable(3));
    REQUIRE_FALSE(rules.IsNextStateStable(4));
    REQUIRE(rules.IsNextStateStable(5));
    REQUIRE_FALSE(rules.IsNextStateStable(6));
    REQUIRE(rules.IsNextStateStable(7));
    REQUIRE_FALSE(rules.IsNextStateStable(8));

    REQUIRE_FALSE(rules.IsNextStateBirth(0));
    REQUIRE(rules.IsNextStateBirth(1));
    REQUIRE_FALSE(rules.IsNextStateBirth(2));
    REQUIRE(rules.IsNextStateBirth(3));
    REQUIRE_FALSE(rules.IsNextStateBirth(4));
    REQUIRE(rules.IsNextStateBirth(5));
    REQUIRE_FALSE(rules.IsNextStateBirth(6));
    REQUIRE(rules.IsNextStateBirth(7));
    REQUIRE_FALSE(rules.IsNextStateBirth(8));
}