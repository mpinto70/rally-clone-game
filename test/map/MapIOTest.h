#pragma once

#include <gtest/gtest.h>

namespace map {

class MapIOTest : public ::testing::Test {
protected:
    void TearDown() override;
};
}
