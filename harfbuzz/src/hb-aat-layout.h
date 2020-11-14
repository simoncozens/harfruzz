/*
 * Copyright © 2018  Ebrahim Byagowi
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#ifndef RB_AAT_H_IN
#error "Include <hb-aat.h> instead."
#endif

#ifndef RB_AAT_LAYOUT_H
#define RB_AAT_LAYOUT_H

#include "hb.h"

RB_BEGIN_DECLS

/**
 * rb_aat_layout_feature_type_t:
 *
 *
 * Since: 2.2.0
 */
typedef enum {
    RB_AAT_LAYOUT_FEATURE_TYPE_INVALID = 0xFFFF,

    RB_AAT_LAYOUT_FEATURE_TYPE_ALL_TYPOGRAPHIC = 0,
    RB_AAT_LAYOUT_FEATURE_TYPE_LIGATURES = 1,
    RB_AAT_LAYOUT_FEATURE_TYPE_CURISVE_CONNECTION = 2,
    RB_AAT_LAYOUT_FEATURE_TYPE_LETTER_CASE = 3,
    RB_AAT_LAYOUT_FEATURE_TYPE_VERTICAL_SUBSTITUTION = 4,
    RB_AAT_LAYOUT_FEATURE_TYPE_LINGUISTIC_REARRANGEMENT = 5,
    RB_AAT_LAYOUT_FEATURE_TYPE_NUMBER_SPACING = 6,
    RB_AAT_LAYOUT_FEATURE_TYPE_SMART_SWASH_TYPE = 8,
    RB_AAT_LAYOUT_FEATURE_TYPE_DIACRITICS_TYPE = 9,
    RB_AAT_LAYOUT_FEATURE_TYPE_VERTICAL_POSITION = 10,
    RB_AAT_LAYOUT_FEATURE_TYPE_FRACTIONS = 11,
    RB_AAT_LAYOUT_FEATURE_TYPE_OVERLAPPING_CHARACTERS_TYPE = 13,
    RB_AAT_LAYOUT_FEATURE_TYPE_TYPOGRAPHIC_EXTRAS = 14,
    RB_AAT_LAYOUT_FEATURE_TYPE_MATHEMATICAL_EXTRAS = 15,
    RB_AAT_LAYOUT_FEATURE_TYPE_ORNAMENT_SETS_TYPE = 16,
    RB_AAT_LAYOUT_FEATURE_TYPE_CHARACTER_ALTERNATIVES = 17,
    RB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE = 18,
    RB_AAT_LAYOUT_FEATURE_TYPE_STYLE_OPTIONS = 19,
    RB_AAT_LAYOUT_FEATURE_TYPE_CHARACTER_SHAPE = 20,
    RB_AAT_LAYOUT_FEATURE_TYPE_NUMBER_CASE = 21,
    RB_AAT_LAYOUT_FEATURE_TYPE_TEXT_SPACING = 22,
    RB_AAT_LAYOUT_FEATURE_TYPE_TRANSLITERATION = 23,
    RB_AAT_LAYOUT_FEATURE_TYPE_ANNOTATION_TYPE = 24,
    RB_AAT_LAYOUT_FEATURE_TYPE_KANA_SPACING_TYPE = 25,
    RB_AAT_LAYOUT_FEATURE_TYPE_IDEOGRAPHIC_SPACING_TYPE = 26,
    RB_AAT_LAYOUT_FEATURE_TYPE_UNICODE_DECOMPOSITION_TYPE = 27,
    RB_AAT_LAYOUT_FEATURE_TYPE_RUBY_KANA = 28,
    RB_AAT_LAYOUT_FEATURE_TYPE_CJK_SYMBOL_ALTERNATIVES_TYPE = 29,
    RB_AAT_LAYOUT_FEATURE_TYPE_IDEOGRAPHIC_ALTERNATIVES_TYPE = 30,
    RB_AAT_LAYOUT_FEATURE_TYPE_CJK_VERTICAL_ROMAN_PLACEMENT_TYPE = 31,
    RB_AAT_LAYOUT_FEATURE_TYPE_ITALIC_CJK_ROMAN = 32,
    RB_AAT_LAYOUT_FEATURE_TYPE_CASE_SENSITIVE_LAYOUT = 33,
    RB_AAT_LAYOUT_FEATURE_TYPE_ALTERNATE_KANA = 34,
    RB_AAT_LAYOUT_FEATURE_TYPE_STYLISTIC_ALTERNATIVES = 35,
    RB_AAT_LAYOUT_FEATURE_TYPE_CONTEXTUAL_ALTERNATIVES = 36,
    RB_AAT_LAYOUT_FEATURE_TYPE_LOWER_CASE = 37,
    RB_AAT_LAYOUT_FEATURE_TYPE_UPPER_CASE = 38,
    RB_AAT_LAYOUT_FEATURE_TYPE_LANGUAGE_TAG_TYPE = 39,
    RB_AAT_LAYOUT_FEATURE_TYPE_CJK_ROMAN_SPACING_TYPE = 103,

    _RB_AAT_LAYOUT_FEATURE_TYPE_MAX_VALUE = RB_TAG_MAX_SIGNED /*< skip >*/
} rb_aat_layout_feature_type_t;

/**
 * rb_aat_layout_feature_selector_t:
 *
 *
 * Since: 2.2.0
 */
typedef enum {
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INVALID = 0xFFFF,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_ALL_TYPOGRAPHIC */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALL_TYPE_FEATURES_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALL_TYPE_FEATURES_OFF = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_LIGATURES */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_REQUIRED_LIGATURES_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_REQUIRED_LIGATURES_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_COMMON_LIGATURES_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_COMMON_LIGATURES_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_RARE_LIGATURES_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_RARE_LIGATURES_OFF = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LOGOS_ON = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LOGOS_OFF = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_REBUS_PICTURES_ON = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_REBUS_PICTURES_OFF = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DIPHTHONG_LIGATURES_ON = 10,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DIPHTHONG_LIGATURES_OFF = 11,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SQUARED_LIGATURES_ON = 12,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SQUARED_LIGATURES_OFF = 13,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ABBREV_SQUARED_LIGATURES_ON = 14,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ABBREV_SQUARED_LIGATURES_OFF = 15,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SYMBOL_LIGATURES_ON = 16,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SYMBOL_LIGATURES_OFF = 17,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_LIGATURES_ON = 18,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_LIGATURES_OFF = 19,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HISTORICAL_LIGATURES_ON = 20,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HISTORICAL_LIGATURES_OFF = 21,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_LIGATURES */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_UNCONNECTED = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PARTIALLY_CONNECTED = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CURSIVE = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_LETTER_CASE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_UPPER_AND_LOWER_CASE = 0,        /* deprecated */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALL_CAPS = 1,                    /* deprecated */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALL_LOWER_CASE = 2,              /* deprecated */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SMALL_CAPS = 3,                  /* deprecated */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INITIAL_CAPS = 4,                /* deprecated */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INITIAL_CAPS_AND_SMALL_CAPS = 5, /* deprecated */

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_VERTICAL_SUBSTITUTION */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SUBSTITUTE_VERTICAL_FORMS_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SUBSTITUTE_VERTICAL_FORMS_OFF = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_LINGUISTIC_REARRANGEMENT */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINGUISTIC_REARRANGEMENT_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINGUISTIC_REARRANGEMENT_OFF = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_NUMBER_SPACING */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_MONOSPACED_NUMBERS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PROPORTIONAL_NUMBERS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_THIRD_WIDTH_NUMBERS = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_QUARTER_WIDTH_NUMBERS = 3,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_SMART_SWASH_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_WORD_INITIAL_SWASHES_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_WORD_INITIAL_SWASHES_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_WORD_FINAL_SWASHES_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_WORD_FINAL_SWASHES_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINE_INITIAL_SWASHES_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINE_INITIAL_SWASHES_OFF = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINE_FINAL_SWASHES_ON = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LINE_FINAL_SWASHES_OFF = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NON_FINAL_SWASHES_ON = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NON_FINAL_SWASHES_OFF = 9,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_DIACRITICS_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SHOW_DIACRITICS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HIDE_DIACRITICS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DECOMPOSE_DIACRITICS = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_VERTICAL_POSITION */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NORMAL_POSITION = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SUPERIORS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INFERIORS = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ORDINALS = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SCIENTIFIC_INFERIORS = 4,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_FRACTIONS */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_FRACTIONS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_VERTICAL_FRACTIONS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DIAGONAL_FRACTIONS = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_OVERLAPPING_CHARACTERS_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PREVENT_OVERLAP_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PREVENT_OVERLAP_OFF = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_TYPOGRAPHIC_EXTRAS */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHENS_TO_EM_DASH_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHENS_TO_EM_DASH_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHEN_TO_EN_DASH_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHEN_TO_EN_DASH_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SLASHED_ZERO_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SLASHED_ZERO_OFF = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FORM_INTERROBANG_ON = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FORM_INTERROBANG_OFF = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SMART_QUOTES_ON = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SMART_QUOTES_OFF = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PERIODS_TO_ELLIPSIS_ON = 10,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PERIODS_TO_ELLIPSIS_OFF = 11,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_MATHEMATICAL_EXTRAS */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHEN_TO_MINUS_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HYPHEN_TO_MINUS_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ASTERISK_TO_MULTIPLY_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ASTERISK_TO_MULTIPLY_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SLASH_TO_DIVIDE_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SLASH_TO_DIVIDE_OFF = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INEQUALITY_LIGATURES_ON = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INEQUALITY_LIGATURES_OFF = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_EXPONENTS_ON = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_EXPONENTS_OFF = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_MATHEMATICAL_GREEK_ON = 10,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_MATHEMATICAL_GREEK_OFF = 11,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_ORNAMENT_SETS_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_ORNAMENTS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DINGBATS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PI_CHARACTERS = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FLEURONS = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DECORATIVE_BORDERS = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INTERNATIONAL_SYMBOLS = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_MATH_SYMBOLS = 6,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CHARACTER_ALTERNATIVES */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_ALTERNATES = 0,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DESIGN_LEVEL1 = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DESIGN_LEVEL2 = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DESIGN_LEVEL3 = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DESIGN_LEVEL4 = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DESIGN_LEVEL5 = 4,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_STYLE_OPTIONS */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_STYLE_OPTIONS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DISPLAY_TEXT = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ENGRAVED_TEXT = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ILLUMINATED_CAPS = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TITLING_CAPS = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TALL_CAPS = 5,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CHARACTER_SHAPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_CHARACTERS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SIMPLIFIED_CHARACTERS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_JIS1978_CHARACTERS = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_JIS1983_CHARACTERS = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_JIS1990_CHARACTERS = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_ALT_ONE = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_ALT_TWO = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_ALT_THREE = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_ALT_FOUR = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_ALT_FIVE = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_EXPERT_CHARACTERS = 10,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_JIS2004_CHARACTERS = 11,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HOJO_CHARACTERS = 12,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NLCCHARACTERS = 13,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRADITIONAL_NAMES_CHARACTERS = 14,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_NUMBER_CASE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LOWER_CASE_NUMBERS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_UPPER_CASE_NUMBERS = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_TEXT_SPACING */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PROPORTIONAL_TEXT = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_MONOSPACED_TEXT = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HALF_WIDTH_TEXT = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_THIRD_WIDTH_TEXT = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_QUARTER_WIDTH_TEXT = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALT_PROPORTIONAL_TEXT = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALT_HALF_WIDTH_TEXT = 6,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_TRANSLITERATION */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_TRANSLITERATION = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HANJA_TO_HANGUL = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HIRAGANA_TO_KATAKANA = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_KATAKANA_TO_HIRAGANA = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_KANA_TO_ROMANIZATION = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ROMANIZATION_TO_HIRAGANA = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ROMANIZATION_TO_KATAKANA = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HANJA_TO_HANGUL_ALT_ONE = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HANJA_TO_HANGUL_ALT_TWO = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HANJA_TO_HANGUL_ALT_THREE = 9,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_ANNOTATION_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_ANNOTATION = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_BOX_ANNOTATION = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ROUNDED_BOX_ANNOTATION = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CIRCLE_ANNOTATION = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INVERTED_CIRCLE_ANNOTATION = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PARENTHESIS_ANNOTATION = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PERIOD_ANNOTATION = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ROMAN_NUMERAL_ANNOTATION = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DIAMOND_ANNOTATION = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INVERTED_BOX_ANNOTATION = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_INVERTED_ROUNDED_BOX_ANNOTATION = 10,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_KANA_SPACING_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FULL_WIDTH_KANA = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PROPORTIONAL_KANA = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_IDEOGRAPHIC_SPACING_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FULL_WIDTH_IDEOGRAPHS = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PROPORTIONAL_IDEOGRAPHS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HALF_WIDTH_IDEOGRAPHS = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_UNICODE_DECOMPOSITION_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CANONICAL_COMPOSITION_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CANONICAL_COMPOSITION_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_COMPATIBILITY_COMPOSITION_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_COMPATIBILITY_COMPOSITION_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRANSCODING_COMPOSITION_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_TRANSCODING_COMPOSITION_OFF = 5,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_RUBY_KANA */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_RUBY_KANA =
        0, /* deprecated - use RB_AAT_LAYOUT_FEATURE_SELECTOR_RUBY_KANA_OFF instead */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_RUBY_KANA =
        1, /* deprecated - use RB_AAT_LAYOUT_FEATURE_SELECTOR_RUBY_KANA_ON instead */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_RUBY_KANA_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_RUBY_KANA_OFF = 3,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CJK_SYMBOL_ALTERNATIVES_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_CJK_SYMBOL_ALTERNATIVES = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_SYMBOL_ALT_ONE = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_SYMBOL_ALT_TWO = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_SYMBOL_ALT_THREE = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_SYMBOL_ALT_FOUR = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_SYMBOL_ALT_FIVE = 5,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_IDEOGRAPHIC_ALTERNATIVES_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_IDEOGRAPHIC_ALTERNATIVES = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_IDEOGRAPHIC_ALT_ONE = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_IDEOGRAPHIC_ALT_TWO = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_IDEOGRAPHIC_ALT_THREE = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_IDEOGRAPHIC_ALT_FOUR = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_IDEOGRAPHIC_ALT_FIVE = 5,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CJK_VERTICAL_ROMAN_PLACEMENT_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_VERTICAL_ROMAN_CENTERED = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_VERTICAL_ROMAN_HBASELINE = 1,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_ITALIC_CJK_ROMAN */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_CJK_ITALIC_ROMAN =
        0, /* deprecated - use RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_ITALIC_ROMAN_OFF instead */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_ITALIC_ROMAN =
        1, /* deprecated - use RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_ITALIC_ROMAN_ON instead */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_ITALIC_ROMAN_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CJK_ITALIC_ROMAN_OFF = 3,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CASE_SENSITIVE_LAYOUT */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CASE_SENSITIVE_LAYOUT_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CASE_SENSITIVE_LAYOUT_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CASE_SENSITIVE_SPACING_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CASE_SENSITIVE_SPACING_OFF = 3,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_ALTERNATE_KANA */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALTERNATE_HORIZ_KANA_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALTERNATE_HORIZ_KANA_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALTERNATE_VERT_KANA_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_ALTERNATE_VERT_KANA_OFF = 3,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_STYLISTIC_ALTERNATIVES */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_NO_STYLISTIC_ALTERNATES = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_ONE_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_ONE_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWO_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWO_OFF = 5,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_THREE_ON = 6,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_THREE_OFF = 7,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FOUR_ON = 8,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FOUR_OFF = 9,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FIVE_ON = 10,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FIVE_OFF = 11,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SIX_ON = 12,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SIX_OFF = 13,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SEVEN_ON = 14,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SEVEN_OFF = 15,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_EIGHT_ON = 16,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_EIGHT_OFF = 17,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_NINE_ON = 18,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_NINE_OFF = 19,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TEN_ON = 20,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TEN_OFF = 21,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_ELEVEN_ON = 22,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_ELEVEN_OFF = 23,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWELVE_ON = 24,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWELVE_OFF = 25,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_THIRTEEN_ON = 26,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_THIRTEEN_OFF = 27,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FOURTEEN_ON = 28,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FOURTEEN_OFF = 29,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FIFTEEN_ON = 30,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_FIFTEEN_OFF = 31,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SIXTEEN_ON = 32,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SIXTEEN_OFF = 33,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SEVENTEEN_ON = 34,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_SEVENTEEN_OFF = 35,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_EIGHTEEN_ON = 36,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_EIGHTEEN_OFF = 37,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_NINETEEN_ON = 38,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_NINETEEN_OFF = 39,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWENTY_ON = 40,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_STYLISTIC_ALT_TWENTY_OFF = 41,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CONTEXTUAL_ALTERNATIVES */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_ALTERNATES_ON = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_ALTERNATES_OFF = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SWASH_ALTERNATES_ON = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_SWASH_ALTERNATES_OFF = 3,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_SWASH_ALTERNATES_ON = 4,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_CONTEXTUAL_SWASH_ALTERNATES_OFF = 5,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_LOWER_CASE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DEFAULT_LOWER_CASE = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LOWER_CASE_SMALL_CAPS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_LOWER_CASE_PETITE_CAPS = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_UPPER_CASE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DEFAULT_UPPER_CASE = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_UPPER_CASE_SMALL_CAPS = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_UPPER_CASE_PETITE_CAPS = 2,

    /* Selectors for #RB_AAT_LAYOUT_FEATURE_TYPE_CJK_ROMAN_SPACING_TYPE */
    RB_AAT_LAYOUT_FEATURE_SELECTOR_HALF_WIDTH_CJK_ROMAN = 0,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_PROPORTIONAL_CJK_ROMAN = 1,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_DEFAULT_CJK_ROMAN = 2,
    RB_AAT_LAYOUT_FEATURE_SELECTOR_FULL_WIDTH_CJK_ROMAN = 3,

    _RB_AAT_LAYOUT_FEATURE_SELECTOR_MAX_VALUE = RB_TAG_MAX_SIGNED /*< skip >*/
} rb_aat_layout_feature_selector_t;

typedef unsigned int rb_ot_name_id_t;

typedef struct rb_aat_layout_feature_selector_info_t
{
    rb_ot_name_id_t name_id;
    rb_aat_layout_feature_selector_t enable;
    rb_aat_layout_feature_selector_t disable;
    /*< private >*/
    unsigned int reserved;
} rb_aat_layout_feature_selector_info_t;

#define RB_AAT_LAYOUT_NO_SELECTOR_INDEX 0xFFFFu

/*
 * morx/mort
 */

RB_EXTERN rb_bool_t rb_aat_layout_has_substitution(rb_face_t *face);

RB_EXTERN void rb_aat_layout_substitute(const rb_shape_plan_t *plan, rb_face_t *face, rb_buffer_t *buffer);

RB_EXTERN void rb_aat_layout_zero_width_deleted_glyphs(rb_buffer_t *buffer);

RB_EXTERN void rb_aat_layout_remove_deleted_glyphs(rb_buffer_t *buffer);

/*
 * kerx
 */

RB_EXTERN rb_bool_t rb_aat_layout_has_positioning(rb_face_t *face);

RB_EXTERN void rb_aat_layout_position(const rb_shape_plan_t *plan, rb_face_t *face, rb_buffer_t *buffer);

/*
 * trak
 */

RB_EXTERN rb_bool_t rb_aat_layout_has_tracking(rb_face_t *face);

RB_EXTERN void rb_aat_layout_track(const rb_shape_plan_t *plan, rb_face_t *face, rb_buffer_t *buffer);

RB_END_DECLS

#endif /* RB_AAT_LAYOUT_H */
