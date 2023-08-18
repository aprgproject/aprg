#pragma once

#include <CPlusPlus/Analyzer/TermAnalyzer.hpp>
#include <CPlusPlus/Database/CPlusPlusDatabase.hpp>
#include <CPlusPlus/Findings/Findings.hpp>
#include <CPlusPlus/Translator/TermTranslator.hpp>
#include <MtDirectoryConstants.hpp>

#include <gtest/gtest.h>

struct ModuleTest : public ::testing::Test {
    ModuleTest();
    void processFile();
    codeReview::CPlusPlusDatabase m_database;
    codeReview::Findings m_findings;
    codeReview::DequeOfTerms m_terms;
    codeReview::TermTranslator m_termTranslator;
    codeReview::TermAnalyzer m_termAnalyzer;
};
