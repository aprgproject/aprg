#pragma once

#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#define EXPECT_PATH_EQ(path1, path2) \
    EXPECT_EQ(AlbaLocalPathHandler(path1).getPath(), AlbaLocalPathHandler(path2).getPath())
