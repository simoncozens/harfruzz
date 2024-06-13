#![allow(
    dead_code,
    non_upper_case_globals,
    unused_assignments,
    unused_parens,
    while_true,
    clippy::assign_op_pattern,
    clippy::collapsible_if,
    clippy::comparison_chain,
    clippy::double_parens,
    clippy::unnecessary_cast,
    clippy::single_match,
    clippy::never_loop
)]

use core::cell::Cell;

use super::buffer::{hb_buffer_t, HB_BUFFER_SCRATCH_FLAG_HAS_BROKEN_SYLLABLE};
use super::hb_glyph_info_t;
use super::machine_cursor::MachineCursor;
use super::ot_layout::*;
use super::ot_shaper_use::category;

static _use_syllable_machine_trans_keys: [u8; 226] = [
    0, 36, 5, 33, 5, 33, 1, 33, 10, 33, 11, 32, 12, 32, 13, 32, 30, 31, 31, 31, 11, 33, 11, 33, 11,
    33, 1, 1, 11, 33, 9, 33, 10, 33, 10, 33, 10, 33, 6, 33, 6, 33, 6, 33, 6, 33, 5, 33, 1, 1, 5,
    33, 26, 27, 27, 27, 5, 33, 5, 33, 1, 33, 10, 33, 11, 32, 12, 32, 13, 32, 30, 31, 31, 31, 11,
    33, 11, 33, 11, 33, 1, 1, 11, 33, 9, 33, 10, 33, 10, 33, 10, 33, 6, 33, 6, 33, 6, 33, 6, 33, 5,
    33, 1, 1, 7, 7, 3, 3, 5, 33, 5, 33, 1, 33, 10, 33, 11, 32, 12, 32, 13, 32, 30, 31, 31, 31, 11,
    33, 11, 33, 11, 33, 1, 1, 11, 33, 9, 33, 10, 33, 10, 33, 10, 33, 6, 33, 6, 33, 6, 33, 6, 33, 5,
    33, 1, 1, 5, 33, 5, 33, 1, 33, 10, 33, 11, 32, 12, 32, 13, 32, 30, 31, 31, 31, 11, 33, 11, 33,
    11, 33, 1, 1, 11, 33, 9, 33, 10, 33, 10, 33, 10, 33, 6, 33, 6, 33, 6, 33, 6, 33, 5, 33, 1, 1,
    3, 3, 7, 7, 1, 33, 5, 33, 26, 27, 27, 27, 1, 4, 35, 37, 34, 37, 34, 36, 0, 0,
];
static _use_syllable_machine_char_class: [i8; 55] = [
    0, 1, 2, 2, 3, 4, 2, 2, 2, 2, 2, 5, 6, 7, 2, 2, 2, 2, 8, 2, 2, 2, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 2, 23, 24, 25, 2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    0, 0,
];
static _use_syllable_machine_index_offsets: [i16; 114] = [
    0, 37, 66, 95, 128, 152, 174, 195, 215, 217, 218, 241, 264, 287, 288, 311, 336, 360, 384, 408,
    436, 464, 492, 520, 549, 550, 579, 581, 582, 611, 640, 673, 697, 719, 740, 760, 762, 763, 786,
    809, 832, 833, 856, 881, 905, 929, 953, 981, 1009, 1037, 1065, 1094, 1095, 1096, 1097, 1126,
    1155, 1188, 1212, 1234, 1255, 1275, 1277, 1278, 1301, 1324, 1347, 1348, 1371, 1396, 1420, 1444,
    1468, 1496, 1524, 1552, 1580, 1609, 1610, 1639, 1668, 1701, 1725, 1747, 1768, 1788, 1790, 1791,
    1814, 1837, 1860, 1861, 1884, 1909, 1933, 1957, 1981, 2009, 2037, 2065, 2093, 2122, 2123, 2124,
    2125, 2158, 2187, 2189, 2190, 2194, 2197, 2201, 0, 0,
];
static _use_syllable_machine_indices: [i8; 2206] = [
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 32, 33, 30, 34, 3, 35, 37, 38, 36, 36, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 36, 58, 59, 60, 61, 58, 37, 38, 36, 36, 39, 40, 41, 42,
    43, 44, 45, 46, 47, 49, 49, 50, 51, 52, 53, 54, 55, 36, 36, 36, 58, 59, 60, 61, 58, 37, 36, 36,
    36, 36, 36, 36, 36, 36, 40, 41, 42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 53, 54, 55, 36, 36,
    36, 36, 59, 60, 61, 62, 40, 41, 42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 53, 54, 55, 36, 36,
    36, 36, 59, 60, 61, 62, 41, 42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 59, 60, 61, 42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 59, 60,
    61, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 59, 60, 61, 59, 60, 60,
    41, 42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 41,
    42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 41, 42,
    43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 55, 36, 36, 36, 36, 59, 60, 61, 62, 63, 41, 42,
    43, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 59, 60, 61, 62, 39, 40, 41,
    42, 43, 36, 36, 36, 36, 36, 36, 50, 51, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 40, 41,
    42, 43, 36, 36, 36, 36, 36, 36, 50, 51, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 40, 41,
    42, 43, 36, 36, 36, 36, 36, 36, 36, 51, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 40, 41,
    42, 43, 36, 36, 36, 36, 36, 36, 36, 36, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 40, 36,
    36, 39, 40, 41, 42, 43, 36, 45, 46, 36, 36, 36, 50, 51, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60,
    61, 62, 40, 36, 36, 39, 40, 41, 42, 43, 36, 36, 46, 36, 36, 36, 50, 51, 52, 53, 54, 55, 36, 36,
    36, 36, 59, 60, 61, 62, 40, 36, 36, 39, 40, 41, 42, 43, 36, 36, 36, 36, 36, 36, 50, 51, 52, 53,
    54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 40, 36, 36, 39, 40, 41, 42, 43, 44, 45, 46, 36, 36, 36,
    50, 51, 52, 53, 54, 55, 36, 36, 36, 36, 59, 60, 61, 62, 37, 38, 36, 36, 39, 40, 41, 42, 43, 44,
    45, 46, 47, 36, 49, 50, 51, 52, 53, 54, 55, 36, 36, 36, 58, 59, 60, 61, 58, 37, 37, 38, 36, 36,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 36, 36, 36, 58, 59, 60, 61,
    58, 56, 57, 57, 65, 66, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 75, 2, 76, 77, 78, 79, 80, 81,
    82, 64, 64, 64, 83, 84, 85, 86, 87, 65, 66, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 76,
    77, 78, 79, 80, 81, 82, 64, 64, 64, 83, 84, 85, 86, 87, 65, 64, 64, 64, 64, 64, 64, 64, 64, 68,
    69, 70, 71, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68,
    69, 70, 71, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 69,
    70, 71, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 84, 85, 86, 70, 71, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 84, 85, 86, 71, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 84, 85, 86, 84, 85, 85, 69, 70, 71, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 69, 70, 71, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 69, 70, 71, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 82, 64, 64, 64, 64, 84, 85, 86, 88, 90, 69, 70, 71, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 84, 85, 86, 88, 67, 68, 69, 70, 71, 64, 64, 64, 64, 64,
    64, 77, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68, 69, 70, 71, 64, 64, 64, 64, 64,
    64, 77, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68, 69, 70, 71, 64, 64, 64, 64, 64,
    64, 64, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68, 69, 70, 71, 64, 64, 64, 64, 64,
    64, 64, 64, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68, 64, 64, 67, 68, 69, 70, 71, 64,
    73, 74, 64, 64, 64, 77, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68, 64, 64, 67, 68,
    69, 70, 71, 64, 64, 74, 64, 64, 64, 77, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84, 85, 86, 88, 68,
    64, 64, 67, 68, 69, 70, 71, 64, 64, 64, 64, 64, 64, 77, 78, 79, 80, 81, 82, 64, 64, 64, 64, 84,
    85, 86, 88, 68, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 64, 64, 64, 77, 78, 79, 80, 81, 82, 64,
    64, 64, 64, 84, 85, 86, 88, 65, 66, 64, 64, 67, 68, 69, 70, 71, 72, 73, 74, 75, 64, 76, 77, 78,
    79, 80, 81, 82, 64, 64, 64, 83, 84, 85, 86, 87, 65, 93, 4, 95, 96, 64, 64, 97, 98, 99, 100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 56, 57, 64, 114, 115, 116, 86,
    117, 95, 96, 64, 64, 97, 98, 99, 100, 101, 102, 103, 104, 105, 107, 107, 108, 109, 110, 111,
    112, 113, 64, 64, 64, 114, 115, 116, 86, 117, 95, 64, 64, 64, 64, 64, 64, 64, 64, 98, 99, 100,
    101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98,
    99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86,
    118, 99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 115, 116,
    86, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 115, 116, 86,
    101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 115, 116, 86, 115, 116,
    116, 99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 111, 112, 113, 64, 64, 64, 64, 115, 116,
    86, 118, 99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 112, 113, 64, 64, 64, 64, 115,
    116, 86, 118, 99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 113, 64, 64, 64, 64,
    115, 116, 86, 118, 119, 99, 100, 101, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 115, 116, 86, 118, 97, 98, 99, 100, 101, 64, 64, 64, 64, 64, 64, 108, 109, 110, 111,
    112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 99, 100, 101, 64, 64, 64, 64, 64, 64, 108,
    109, 110, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 99, 100, 101, 64, 64, 64, 64,
    64, 64, 64, 109, 110, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 99, 100, 101, 64,
    64, 64, 64, 64, 64, 64, 64, 110, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 64, 64,
    97, 98, 99, 100, 101, 64, 103, 104, 64, 64, 64, 108, 109, 110, 111, 112, 113, 64, 64, 64, 64,
    115, 116, 86, 118, 98, 64, 64, 97, 98, 99, 100, 101, 64, 64, 104, 64, 64, 64, 108, 109, 110,
    111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 64, 64, 97, 98, 99, 100, 101, 64, 64, 64,
    64, 64, 64, 108, 109, 110, 111, 112, 113, 64, 64, 64, 64, 115, 116, 86, 118, 98, 64, 64, 97,
    98, 99, 100, 101, 102, 103, 104, 64, 64, 64, 108, 109, 110, 111, 112, 113, 64, 64, 64, 64, 115,
    116, 86, 118, 95, 96, 64, 64, 97, 98, 99, 100, 101, 102, 103, 104, 105, 64, 107, 108, 109, 110,
    111, 112, 113, 64, 64, 64, 114, 115, 116, 86, 117, 95, 95, 96, 64, 64, 97, 98, 99, 100, 101,
    102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 64, 64, 64, 114, 115, 116, 86, 117,
    6, 7, 120, 120, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20, 20, 21, 22, 23, 24, 25, 26, 120, 120,
    120, 30, 31, 32, 33, 30, 6, 120, 120, 120, 120, 120, 120, 120, 120, 11, 12, 13, 14, 120, 120,
    120, 120, 120, 120, 120, 120, 120, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 11, 12, 13,
    14, 120, 120, 120, 120, 120, 120, 120, 120, 120, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33,
    121, 12, 13, 14, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
    120, 31, 32, 33, 13, 14, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
    120, 120, 31, 32, 33, 14, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
    120, 120, 31, 32, 33, 31, 32, 32, 12, 13, 14, 120, 120, 120, 120, 120, 120, 120, 120, 120, 24,
    25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 12, 13, 14, 120, 120, 120, 120, 120, 120, 120,
    120, 120, 120, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 12, 13, 14, 120, 120, 120, 120,
    120, 120, 120, 120, 120, 120, 120, 26, 120, 120, 120, 120, 31, 32, 33, 121, 122, 12, 13, 14,
    120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 31, 32, 33,
    121, 10, 11, 12, 13, 14, 120, 120, 120, 120, 120, 120, 21, 22, 23, 24, 25, 26, 120, 120, 120,
    120, 31, 32, 33, 121, 11, 12, 13, 14, 120, 120, 120, 120, 120, 120, 21, 22, 23, 24, 25, 26,
    120, 120, 120, 120, 31, 32, 33, 121, 11, 12, 13, 14, 120, 120, 120, 120, 120, 120, 120, 22, 23,
    24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 11, 12, 13, 14, 120, 120, 120, 120, 120, 120,
    120, 120, 23, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 11, 120, 120, 10, 11, 12, 13,
    14, 120, 16, 17, 120, 120, 120, 21, 22, 23, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121,
    11, 120, 120, 10, 11, 12, 13, 14, 120, 120, 17, 120, 120, 120, 21, 22, 23, 24, 25, 26, 120,
    120, 120, 120, 31, 32, 33, 121, 11, 120, 120, 10, 11, 12, 13, 14, 120, 120, 120, 120, 120, 120,
    21, 22, 23, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 11, 120, 120, 10, 11, 12, 13, 14,
    15, 16, 17, 120, 120, 120, 21, 22, 23, 24, 25, 26, 120, 120, 120, 120, 31, 32, 33, 121, 6, 7,
    120, 120, 10, 11, 12, 13, 14, 15, 16, 17, 18, 120, 20, 21, 22, 23, 24, 25, 26, 120, 120, 120,
    30, 31, 32, 33, 30, 6, 123, 8, 2, 120, 120, 2, 6, 7, 8, 120, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 120, 30, 31, 32, 33, 30, 6, 7, 120, 120, 10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 120, 120, 120, 30, 31, 32, 33, 30,
    27, 28, 28, 2, 124, 124, 2, 126, 125, 34, 34, 126, 125, 126, 34, 125, 35, 0, 0,
];
static _use_syllable_machine_index_defaults: [i8; 114] = [
    3, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
    36, 36, 36, 36, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 89, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 91, 92, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 89, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 91, 64, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
    120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 124, 125, 125,
    125, 0, 0,
];
static _use_syllable_machine_cond_targs: [i8; 129] = [
    0, 1, 28, 0, 52, 54, 79, 80, 102, 104, 92, 81, 82, 83, 84, 96, 97, 98, 99, 105, 100, 93, 94,
    95, 87, 88, 89, 106, 107, 108, 101, 85, 86, 0, 109, 111, 0, 2, 3, 15, 4, 5, 6, 7, 19, 20, 21,
    22, 25, 23, 16, 17, 18, 10, 11, 12, 26, 27, 24, 8, 9, 0, 13, 14, 0, 29, 30, 42, 31, 32, 33, 34,
    46, 47, 48, 49, 50, 43, 44, 45, 37, 38, 39, 51, 35, 36, 0, 51, 40, 0, 41, 0, 0, 53, 0, 55, 56,
    68, 57, 58, 59, 60, 72, 73, 74, 75, 78, 76, 69, 70, 71, 63, 64, 65, 77, 61, 62, 77, 66, 67, 0,
    90, 91, 103, 0, 0, 110, 0, 0,
];
static _use_syllable_machine_cond_actions: [i8; 129] = [
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,
    7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 9, 10, 0, 11, 0, 12, 13, 0,
    14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 10, 0, 0, 15, 0, 0, 0,
    16, 17, 0, 0, 0,
];
static _use_syllable_machine_to_state_actions: [i8; 114] = [
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];
static _use_syllable_machine_from_state_actions: [i8; 114] = [
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
];
static _use_syllable_machine_eof_trans: [i8; 114] = [
    1, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
    37, 37, 37, 37, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 90, 65, 65, 65, 65, 65, 65, 65,
    65, 65, 65, 92, 93, 95, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 90, 65, 65, 65, 65, 65,
    65, 65, 65, 65, 65, 92, 65, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121,
    121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 125, 126, 126,
    126, 0, 0,
];
static use_syllable_machine_start: i32 = 0;
static use_syllable_machine_first_final: i32 = 0;
static use_syllable_machine_error: i32 = -1;
static use_syllable_machine_en_main: i32 = 0;
#[derive(Clone, Copy)]
pub enum SyllableType {
    IndependentCluster,
    ViramaTerminatedCluster,
    SakotTerminatedCluster,
    StandardCluster,
    NumberJoinerTerminatedCluster,
    NumeralCluster,
    SymbolCluster,
    HieroglyphCluster,
    BrokenCluster,
    NonCluster,
}

pub fn find_syllables(buffer: &mut hb_buffer_t) {
    let mut cs = 0;
    let infos = Cell::as_slice_of_cells(Cell::from_mut(&mut buffer.info));
    let p0 = MachineCursor::new(infos, included);
    let mut p = p0;
    let mut ts = p0;
    let mut te = p0;
    let mut act = p0;
    let pe = p.end();
    let eof = p.end();
    let mut syllable_serial = 1u8;

    // Please manually replace assignments of 0 to p, ts, and te
    // to use p0 instead

    macro_rules! found_syllable {
        ($kind:expr) => {{
            found_syllable(ts.index(), te.index(), &mut syllable_serial, $kind, infos);
        }};
    }

    {
        cs = (use_syllable_machine_start) as i32;
        ts = p0;
        te = p0;
        act = p0;
    }

    {
        let mut _trans = 0;
        let mut _keys: i32 = 0;
        let mut _inds: i32 = 0;
        let mut _ic = 0;
        '_resume: while (p != pe || p == eof) {
            '_again: while (true) {
                match (_use_syllable_machine_from_state_actions[(cs) as usize]) {
                    2 => {
                        ts = p;
                    }

                    _ => {}
                }
                if (p == eof) {
                    {
                        if (_use_syllable_machine_eof_trans[(cs) as usize] > 0) {
                            {
                                _trans =
                                    (_use_syllable_machine_eof_trans[(cs) as usize]) as u32 - 1;
                            }
                        }
                    }
                } else {
                    {
                        _keys = (cs << 1) as i32;
                        _inds = (_use_syllable_machine_index_offsets[(cs) as usize]) as i32;
                        if ((infos[p.index()].get().use_category() as u8) <= 52) {
                            {
                                _ic = (_use_syllable_machine_char_class[((infos[p.index()]
                                    .get()
                                    .use_category()
                                    as u8)
                                    as i32
                                    - 0)
                                    as usize]) as i32;
                                if (_ic
                                    <= (_use_syllable_machine_trans_keys[(_keys + 1) as usize])
                                        as i32
                                    && _ic
                                        >= (_use_syllable_machine_trans_keys[(_keys) as usize])
                                            as i32)
                                {
                                    _trans = (_use_syllable_machine_indices[(_inds
                                        + (_ic
                                            - (_use_syllable_machine_trans_keys[(_keys) as usize])
                                                as i32)
                                            as i32)
                                        as usize])
                                        as u32;
                                } else {
                                    _trans = (_use_syllable_machine_index_defaults[(cs) as usize])
                                        as u32;
                                }
                            }
                        } else {
                            {
                                _trans =
                                    (_use_syllable_machine_index_defaults[(cs) as usize]) as u32;
                            }
                        }
                    }
                }
                cs = (_use_syllable_machine_cond_targs[(_trans) as usize]) as i32;
                if (_use_syllable_machine_cond_actions[(_trans) as usize] != 0) {
                    {
                        match (_use_syllable_machine_cond_actions[(_trans) as usize]) {
                            9 => {
                                te = p + 1;
                                {
                                    found_syllable!(SyllableType::StandardCluster);
                                }
                            }
                            6 => {
                                te = p + 1;
                                {
                                    found_syllable!(SyllableType::SymbolCluster);
                                }
                            }
                            4 => {
                                te = p + 1;
                                {
                                    found_syllable!(SyllableType::BrokenCluster);
                                    buffer.scratch_flags |=
                                        HB_BUFFER_SCRATCH_FLAG_HAS_BROKEN_SYLLABLE;
                                }
                            }
                            3 => {
                                te = p + 1;
                                {
                                    found_syllable!(SyllableType::NonCluster);
                                }
                            }
                            11 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::SakotTerminatedCluster);
                                }
                            }
                            7 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::StandardCluster);
                                }
                            }
                            14 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::NumberJoinerTerminatedCluster);
                                }
                            }
                            13 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::NumeralCluster);
                                }
                            }
                            5 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::SymbolCluster);
                                }
                            }
                            17 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::HieroglyphCluster);
                                }
                            }
                            15 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::BrokenCluster);
                                    buffer.scratch_flags |=
                                        HB_BUFFER_SCRATCH_FLAG_HAS_BROKEN_SYLLABLE;
                                }
                            }
                            16 => {
                                te = p;
                                p = p - 1;
                                {
                                    found_syllable!(SyllableType::NonCluster);
                                }
                            }
                            12 => match (act).index() {
                                1 => {
                                    p = (te) - 1;
                                    {
                                        found_syllable!(SyllableType::ViramaTerminatedCluster);
                                    }
                                }
                                2 => {
                                    p = (te) - 1;
                                    {
                                        found_syllable!(SyllableType::SakotTerminatedCluster);
                                    }
                                }

                                _ => {}
                            },
                            8 => {
                                {
                                    {
                                        te = p + 1;
                                    }
                                }
                                {
                                    {
                                        act = p + 1;
                                    }
                                }
                            }
                            10 => {
                                {
                                    {
                                        te = p + 1;
                                    }
                                }
                                {
                                    {
                                        act = p + 2;
                                    }
                                }
                            }

                            _ => {}
                        }
                    }
                }
                break '_again;
            }
            if (p == eof) {
                {
                    if (cs >= 0) {
                        break '_resume;
                    }
                }
            } else {
                {
                    match (_use_syllable_machine_to_state_actions[(cs) as usize]) {
                        1 => {
                            ts = p0;
                        }

                        _ => {}
                    }
                    p += 1;
                    continue '_resume;
                }
            }
            break '_resume;
        }
    }
}

#[inline]
fn found_syllable(
    start: usize,
    end: usize,
    syllable_serial: &mut u8,
    kind: SyllableType,
    buffer: &[Cell<hb_glyph_info_t>],
) {
    for i in start..end {
        let mut glyph = buffer[i].get();
        glyph.set_syllable((*syllable_serial << 4) | kind as u8);
        buffer[i].set(glyph);
    }

    *syllable_serial += 1;

    if *syllable_serial == 16 {
        *syllable_serial = 1;
    }
}

fn not_ccs_default_ignorable(i: &hb_glyph_info_t) -> bool {
    i.use_category() != category::CGJ
}

fn included(infos: &[Cell<hb_glyph_info_t>], i: usize) -> bool {
    let glyph = infos[i].get();
    if !not_ccs_default_ignorable(&glyph) {
        return false;
    }
    if glyph.use_category() == category::ZWNJ {
        for glyph2 in &infos[i + 1..] {
            if not_ccs_default_ignorable(&glyph2.get()) {
                return !_hb_glyph_info_is_unicode_mark(&glyph2.get());
            }
        }
    }
    true
}
