#pragma once

#include <gtest/gtest.h>

namespace map {

class CMapIOTest : public ::testing::Test {
protected:
    void TearDown() override;
};
}
