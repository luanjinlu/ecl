/****************************************************************************
 *
 *   Copyright (c) 2020 Estimation and Control Library (ECL). All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ECL nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <stdint.h>

static constexpr float SAMPLING_RES = 10;
static constexpr float SAMPLING_MIN_LAT = -90;
static constexpr float SAMPLING_MAX_LAT = 90;
static constexpr float SAMPLING_MIN_LON = -180;
static constexpr float SAMPLING_MAX_LON = 180;

static constexpr int LAT_DIM = 19;
static constexpr int LON_DIM = 37;


// Magnetic declination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.6503,
static constexpr const int16_t declination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ {  26034, 24289, 22544, 20798, 19053, 17308, 15562, 13817, 12072, 10326,  8581,  6836,  5091,  3345,  1600,  -145, -1890, -3636, -5381, -7126, -8872,-10617,-12362,-14108,-15853,-17598,-19344,-21089,-22834,-24580,-26325,-28070,-29816, 31271, 29525, 27780, 26034, },
/* LAT: -80 */ {  22606, 20468, 18523, 16744, 15101, 13561, 12095, 10682,  9306,  7955,  6622,  5303,  3994,  2689,  1382,    64, -1275, -2644, -4050, -5498, -6988, -8521,-10095,-11710,-13371,-15086,-16868,-18737,-20716,-22831,-25102,-27534,-30104, 30084, 27459, 24945, 22606, },
/* LAT: -70 */ {  14961, 13567, 12446, 11490, 10627,  9801,  8963,  8079,  7129,  6111,  5041,  3946,  2858,  1800,   775,  -235, -1270, -2369, -3562, -4852, -6224, -7647, -9089,-10527,-11950,-13364,-14788,-16268,-17881,-19777,-22267,-26021, 30895, 24224, 19631, 16835, 14961, },
/* LAT: -60 */ {   8358,  8125,  7857,  7594,  7351,  7106,  6806,  6381,  5772,  4958,  3961,  2849,  1725,   687,  -206,  -973, -1703, -2517, -3505, -4683, -5998, -7357, -8673, -9883,-10950,-11852,-12572,-13069,-13241,-12791,-10711, -3659,  4699,  7522,  8331,  8478,  8358, },
/* LAT: -50 */ {   5436,  5479,  5431,  5351,  5286,  5257,  5229,  5109,  4774,  4120,  3119,  1851,   506,  -690, -1584, -2170, -2579, -3013, -3673, -4653, -5869, -7131, -8271, -9180, -9791,-10048, -9873, -9133, -7640, -5292, -2396,   349,  2457,  3879,  4753,  5229,  5436, },
/* LAT: -40 */ {   3919,  4014,  4029,  3994,  3942,  3915,  3925,  3919,  3753,  3231,  2223,   792,  -776, -2110, -3003, -3482, -3688, -3758, -3908, -4428, -5358, -6416, -7308, -7866, -7998, -7649, -6784, -5411, -3694, -1979,  -511,   713,  1753,  2611,  3262,  3689,  3919, },
/* LAT: -30 */ {   2953,  3041,  3080,  3076,  3026,  2954,  2900,  2870,  2748,  2283,  1269,  -233, -1845, -3122, -3893, -4264, -4369, -4188, -3761, -3491, -3789, -4511, -5220, -5597, -5501, -4940, -3997, -2787, -1561,  -600,    87,   689,  1308,  1901,  2402,  2758,  2953, },
/* LAT: -20 */ {   2311,  2359,  2387,  2400,  2368,  2281,  2181,  2108,  1966,  1483,   450, -1021, -2506, -3595, -4162, -4309, -4134, -3605, -2755, -1927, -1596, -1913, -2559, -3048, -3109, -2770, -2144, -1321,  -528,   -24,   249,   554,   988,  1454,  1865,  2163,  2311, },
/* LAT: -10 */ {   1917,  1914,  1903,  1912,  1894,  1819,  1719,  1634,  1452,   912,  -130, -1496, -2781, -3642, -3948, -3754, -3201, -2431, -1584,  -813,  -321,  -321,  -772, -1285, -1515, -1439, -1131,  -627,  -117,   138,   198,   363,   726,  1148,  1528,  1804,  1917, },
/* LAT:   0 */ {   1705,  1674,  1629,  1631,  1630,  1571,  1479,  1374,  1124,   510,  -518, -1743, -2813, -3432, -3470, -3000, -2243, -1458,  -796,  -252,   172,   305,    46,  -371,  -636,  -698,  -600,  -334,   -34,    66,    18,   112,   444,   870,  1275,  1583,  1705, },
/* LAT:  10 */ {   1575,  1585,  1551,  1577,  1612,  1573,  1465,  1288,   916,   202,  -815, -1896, -2743, -3114, -2942, -2356, -1584,  -865,  -338,    49,   379,   541,   395,    74,  -167,  -276,  -294,  -207,   -95,  -127,  -256,  -225,    68,   507,   974,  1371,  1575, },
/* LAT:  20 */ {   1402,  1552,  1619,  1717,  1810,  1799,  1656,  1364,   823,   -34, -1079, -2043, -2662, -2799, -2494, -1904, -1195,  -539,   -67,   249,   512,   666,   586,   345,   141,    24,   -58,  -113,  -185,  -367,  -597,  -654,  -428,     7,   538,  1049,  1402, },
/* LAT:  30 */ {   1117,  1485,  1747,  1974,  2138,  2154,  1975,  1560,   836,  -196, -1324, -2220, -2659, -2618, -2233, -1660, -1005,  -382,    89,   402,   638,   792,   781,   635,   483,   360,   214,    16,  -256,  -625,  -991, -1153, -1000,  -583,   -12,   595,  1117, },
/* LAT:  40 */ {    778,  1366,  1860,  2251,  2501,  2547,  2335,  1806,   895,  -341, -1598, -2489, -2831, -2693, -2254, -1665, -1012,  -379,   139,   511,   788,   994,  1097,  1091,  1014,   870,   613,   220,  -305,  -907, -1431, -1682, -1573, -1162,  -563,   114,   778, },
/* LAT:  50 */ {    509,  1260,  1939,  2492,  2855,  2958,  2728,  2071,   922,  -594, -2044, -2983, -3293, -3109, -2622, -1977, -1265,  -563,    60,   573,   998,  1361,  1650,  1828,  1853,  1675,  1247,   560,  -318, -1219, -1908, -2207, -2091, -1649, -1007,  -264,   509, },
/* LAT:  60 */ {    344,  1203,  2008,  2698,  3193,  3396,  3172,  2344,   800, -1203, -2956, -3954, -4211, -3948, -3372, -2622, -1791,  -944,  -130,   628,  1327,  1965,  2516,  2922,  3095,  2927,  2315,  1229,  -169, -1495, -2382, -2707, -2546, -2044, -1337,  -519,   344, },
/* LAT:  70 */ {    168,  1114,  2014,  2811,  3417,  3697,  3417,  2221,  -128, -2947, -4927, -5736, -5720, -5216, -4429, -3480, -2445, -1369,  -286,   781,  1813,  2786,  3661,  4379,  4841,  4897,  4325,  2904,   751, -1356, -2674, -3132, -2972, -2429, -1663,  -774,   168, },
/* LAT:  80 */ {   -342,   588,  1450,  2148,  2528,  2301,   944, -2031, -5555, -7682, -8332, -8112, -7419, -6455, -5330, -4106, -2821, -1501,  -165,  1172,  2492,  3778,  5008,  6148,  7145,  7906,  8258,  7851,  6057,  2546,  -920, -2669, -3081, -2781, -2117, -1269,  -342, },
/* LAT:  90 */ { -30543,-28798,-27052,-25307,-23561,-21816,-20071,-18325,-16580,-14835,-13089,-11344, -9599, -7854, -6109, -4363, -2618,  -873,   872,  2617,  4362,  6108,  7853,  9598, 11344, 13089, 14834, 16580, 18325, 20070, 21816, 23561, 25307, 27052, 28798, 30543,-30543, },
};

// Magnetic inclination data in radians * 10^-4
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.6503,
static constexpr const int16_t inclination_table[19][37] {
//    LONGITUDE:   -180,  -170,  -160,  -150,  -140,  -130,  -120,  -110,  -100,   -90,   -80,   -70,   -60,   -50,   -40,   -30,   -20,   -10,     0,    10,    20,    30,    40,    50,    60,    70,    80,    90,   100,   110,   120,   130,   140,   150,   160,   170,   180,
/* LAT: -90 */ { -12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583,-12583, },
/* LAT: -80 */ { -13671,-13538,-13378,-13197,-13003,-12800,-12596,-12395,-12203,-12026,-11868,-11734,-11623,-11537,-11473,-11432,-11413,-11416,-11443,-11497,-11580,-11694,-11838,-12011,-12208,-12425,-12653,-12886,-13114,-13327,-13515,-13666,-13771,-13824,-13822,-13769,-13671, },
/* LAT: -70 */ { -14122,-13804,-13485,-13161,-12829,-12483,-12127,-11768,-11423,-11112,-10857,-10671,-10556,-10503,-10490,-10496,-10506,-10519,-10544,-10601,-10708,-10880,-11123,-11435,-11805,-12220,-12667,-13130,-13596,-14049,-14469,-14818,-15013,-14964,-14735,-14438,-14122, },
/* LAT: -60 */ { -13528,-13177,-12839,-12507,-12164,-11791,-11375,-10919,-10449,-10015, -9679, -9497, -9488, -9621, -9827,-10026,-10160,-10214,-10209,-10198,-10243,-10396,-10677,-11078,-11571,-12123,-12707,-13303,-13891,-14453,-14949,-15241,-15074,-14694,-14291,-13900,-13528, },
/* LAT: -50 */ { -12500,-12160,-11831,-11510,-11187,-10840,-10440, -9968, -9435, -8909, -8510, -8372, -8560, -9014, -9579,-10100,-10475,-10656,-10644,-10503,-10361,-10356,-10562,-10965,-11498,-12087,-12674,-13216,-13665,-13966,-14076,-14005,-13802,-13520,-13193,-12847,-12500, },
/* LAT: -40 */ { -11240,-10896,-10552,-10209, -9869, -9530, -9167, -8739, -8216, -7646, -7207, -7144, -7582, -8395, -9318,-10158,-10831,-11287,-11453,-11310,-10978,-10696,-10668,-10931,-11383,-11887,-12338,-12668,-12834,-12840,-12749,-12610,-12428,-12196,-11910,-11584,-11240, },
/* LAT: -30 */ {  -9600, -9229, -8856, -8469, -8076, -7698, -7337, -6942, -6426, -5811, -5344, -5394, -6130, -7316, -8570, -9677,-10606,-11336,-11765,-11788,-11438,-10932,-10581,-10562,-10802,-11123,-11387,-11510,-11453,-11278,-11099,-10958,-10807,-10597,-10316, -9973, -9600, },
/* LAT: -20 */ {  -7368, -6941, -6534, -6110, -5665, -5232, -4835, -4414, -3842, -3152, -2684, -2901, -3967, -5557, -7192, -8582, -9671,-10471,-10938,-11004,-10665,-10063, -9498, -9238, -9275, -9436, -9582, -9609, -9442, -9168, -8967, -8869, -8754, -8541, -8224, -7816, -7368, },
/* LAT: -10 */ {  -4409, -3893, -3453, -3023, -2566, -2113, -1692, -1225,  -587,   127,   515,   134, -1146, -3038, -5022, -6663, -7795, -8459, -8749, -8710, -8325, -7658, -6993, -6634, -6586, -6678, -6800, -6830, -6646, -6348, -6183, -6174, -6116, -5891, -5508, -4987, -4409, },
/* LAT:   0 */ {   -899,  -298,   151,   546,   962,  1380,  1778,  2238,  2839,  3432,  3659,  3203,  1952,    70, -1980, -3667, -4719, -5180, -5260, -5107, -4688, -3991, -3286, -2903, -2839, -2912, -3041, -3118, -2990, -2751, -2684, -2803, -2842, -2645, -2221, -1601,  -899, },
/* LAT:  10 */ {   2568,  3174,  3593,  3927,  4280,  4648,  5008,  5411,  5880,  6265,  6322,  5862,  4813,  3271,  1577,   173,  -669,  -948,  -875,  -651,  -256,   367,   999,  1344,  1405,  1353,  1248,  1157,  1201,  1310,  1248,  1005,   836,   919,  1270,  1862,  2568, },
/* LAT:  20 */ {   5420,  5934,  6304,  6594,  6906,  7251,  7600,  7960,  8308,  8521,  8449,  8006,  7190,  6107,  4978,  4051,  3497,  3355,  3490,  3724,  4045,  4501,  4959,  5217,  5270,  5245,  5192,  5136,  5129,  5117,  4955,  4640,  4359,  4277,  4448,  4863,  5420, },
/* LAT:  30 */ {   7570,  7936,  8249,  8529,  8837,  9187,  9549,  9899, 10186, 10310, 10176,  9767,  9147,  8439,  7773,  7251,  6946,  6889,  7020,  7225,  7465,  7759,  8045,  8219,  8273,  8279,  8277,  8268,  8251,  8175,  7962,  7620,  7274,  7059,  7042,  7232,  7570, },
/* LAT:  40 */ {   9265,  9485,  9739, 10024, 10352, 10715, 11087, 11432, 11691, 11782, 11639, 11285, 10814, 10338,  9938,  9648,  9490,  9477,  9580,  9736,  9906, 10086, 10256, 10381, 10457, 10513, 10564, 10597, 10585, 10481, 10246,  9902,  9540,  9257,  9114,  9125,  9265, },
/* LAT:  50 */ {  10801, 10923, 11126, 11397, 11722, 12079, 12437, 12758, 12985, 13049, 12913, 12616, 12250, 11901, 11622, 11431, 11332, 11322, 11383, 11482, 11592, 11705, 11820, 11934, 12051, 12170, 12281, 12354, 12349, 12231, 11990, 11666, 11328, 11043, 10853, 10773, 10801, },
/* LAT:  60 */ {  12317, 12393, 12547, 12768, 13041, 13345, 13650, 13920, 14098, 14126, 13990, 13739, 13447, 13173, 12950, 12790, 12695, 12660, 12673, 12717, 12782, 12865, 12968, 13098, 13255, 13429, 13594, 13705, 13716, 13602, 13381, 13103, 12823, 12585, 12415, 12324, 12317, },
/* LAT:  70 */ {  13759, 13805, 13904, 14050, 14234, 14441, 14652, 14835, 14939, 14915, 14772, 14567, 14346, 14140, 13965, 13829, 13733, 13676, 13655, 13666, 13706, 13776, 13877, 14012, 14176, 14362, 14547, 14689, 14740, 14673, 14514, 14316, 14120, 13955, 13836, 13769, 13759, },
/* LAT:  80 */ {  15005, 15020, 15061, 15124, 15204, 15292, 15374, 15418, 15393, 15306, 15188, 15060, 14935, 14820, 14719, 14637, 14574, 14532, 14513, 14516, 14541, 14590, 14660, 14752, 14862, 14988, 15122, 15253, 15360, 15407, 15374, 15291, 15199, 15117, 15054, 15016, 15005, },
/* LAT:  90 */ {  15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15388, 15388, 15388, 15388, 15388, 15388, 15388, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, 15389, },
};

// Magnetic strength data in milli-Gauss * 10
// Model: WMM-2020,
// Version: 0.5.1.11,
// Date: 2020.6503,
static constexpr const int16_t strength_table[19][37] {
//    LONGITUDE:  -180, -170, -160, -150, -140, -130, -120, -110, -100,  -90,  -80,  -70,  -60,  -50,  -40,  -30,  -20,  -10,    0,   10,   20,   30,   40,   50,   60,   70,   80,   90,  100,  110,  120,  130,  140,  150,  160,  170,  180,
/* LAT: -90 */ {  5463, 5463, 5463, 5463, 5463, 5463, 5463, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5462, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, 5463, },
/* LAT: -80 */ {  6069, 6006, 5929, 5837, 5735, 5624, 5507, 5385, 5263, 5143, 5028, 4923, 4829, 4749, 4685, 4639, 4614, 4611, 4632, 4677, 4746, 4839, 4953, 5084, 5227, 5376, 5526, 5669, 5800, 5914, 6007, 6076, 6121, 6142, 6139, 6114, 6069, },
/* LAT: -70 */ {  6313, 6182, 6034, 5871, 5693, 5502, 5297, 5083, 4863, 4648, 4444, 4261, 4102, 3970, 3866, 3788, 3740, 3727, 3754, 3828, 3954, 4132, 4358, 4624, 4918, 5224, 5528, 5812, 6062, 6267, 6419, 6515, 6558, 6553, 6505, 6423, 6313, },
/* LAT: -60 */ {  6197, 6008, 5809, 5602, 5385, 5151, 4895, 4617, 4324, 4034, 3765, 3536, 3355, 3219, 3120, 3046, 2996, 2975, 3000, 3087, 3252, 3500, 3823, 4207, 4627, 5061, 5482, 5866, 6192, 6442, 6608, 6688, 6692, 6631, 6520, 6371, 6197, },
/* LAT: -50 */ {  5853, 5625, 5395, 5167, 4936, 4692, 4422, 4119, 3790, 3458, 3154, 2912, 2748, 2655, 2606, 2573, 2541, 2516, 2521, 2590, 2758, 3042, 3432, 3899, 4404, 4910, 5386, 5807, 6147, 6391, 6531, 6574, 6534, 6426, 6266, 6070, 5853, },
/* LAT: -40 */ {  5399, 5156, 4913, 4675, 4442, 4206, 3952, 3669, 3355, 3029, 2728, 2503, 2382, 2355, 2374, 2398, 2405, 2396, 2385, 2412, 2535, 2801, 3209, 3718, 4263, 4789, 5259, 5650, 5945, 6134, 6224, 6229, 6161, 6032, 5853, 5636, 5399, },
/* LAT: -30 */ {  4882, 4644, 4407, 4174, 3949, 3731, 3513, 3282, 3027, 2752, 2493, 2308, 2234, 2256, 2323, 2395, 2463, 2517, 2544, 2557, 2618, 2805, 3156, 3636, 4166, 4666, 5089, 5411, 5617, 5718, 5746, 5720, 5641, 5510, 5332, 5117, 4882, },
/* LAT: -20 */ {  4323, 4113, 3907, 3703, 3508, 3326, 3158, 2995, 2819, 2622, 2431, 2295, 2248, 2287, 2374, 2485, 2615, 2746, 2841, 2881, 2904, 2991, 3219, 3594, 4040, 4469, 4823, 5064, 5173, 5182, 5152, 5105, 5023, 4896, 4730, 4534, 4323, },
/* LAT: -10 */ {  3791, 3633, 3482, 3337, 3201, 3082, 2979, 2889, 2794, 2682, 2560, 2459, 2408, 2426, 2507, 2635, 2791, 2952, 3082, 3149, 3165, 3187, 3301, 3545, 3866, 4188, 4457, 4625, 4665, 4614, 4546, 4482, 4392, 4267, 4119, 3957, 3791, },
/* LAT:   0 */ {  3413, 3322, 3239, 3168, 3113, 3075, 3051, 3035, 3014, 2968, 2890, 2794, 2709, 2672, 2707, 2806, 2939, 3076, 3194, 3272, 3305, 3326, 3395, 3546, 3751, 3964, 4145, 4255, 4265, 4199, 4111, 4018, 3905, 3774, 3641, 3518, 3413, },
/* LAT:  10 */ {  3283, 3254, 3235, 3233, 3258, 3307, 3365, 3421, 3460, 3452, 3384, 3269, 3139, 3039, 3006, 3042, 3121, 3219, 3320, 3406, 3471, 3532, 3617, 3732, 3864, 4000, 4120, 4193, 4198, 4138, 4030, 3887, 3726, 3567, 3433, 3338, 3283, },
/* LAT:  20 */ {  3400, 3405, 3434, 3490, 3584, 3707, 3838, 3958, 4042, 4055, 3983, 3840, 3670, 3526, 3444, 3427, 3459, 3529, 3624, 3721, 3810, 3907, 4017, 4127, 4233, 4342, 4443, 4510, 4524, 4468, 4333, 4133, 3907, 3698, 3536, 3437, 3400, },
/* LAT:  30 */ {  3724, 3734, 3792, 3894, 4039, 4213, 4391, 4549, 4659, 4687, 4614, 4457, 4265, 4095, 3984, 3934, 3933, 3981, 4065, 4162, 4257, 4361, 4477, 4594, 4713, 4837, 4955, 5042, 5071, 5017, 4864, 4626, 4353, 4100, 3902, 3775, 3724, },
/* LAT:  40 */ {  4223, 4226, 4295, 4422, 4592, 4782, 4967, 5124, 5229, 5255, 5186, 5036, 4845, 4666, 4533, 4454, 4424, 4443, 4500, 4577, 4662, 4757, 4871, 5005, 5155, 5315, 5465, 5576, 5619, 5568, 5415, 5179, 4905, 4646, 4436, 4293, 4223, },
/* LAT:  50 */ {  4831, 4830, 4891, 5005, 5155, 5315, 5466, 5586, 5659, 5667, 5602, 5472, 5306, 5139, 4999, 4898, 4840, 4825, 4847, 4896, 4963, 5052, 5170, 5320, 5494, 5678, 5845, 5965, 6013, 5973, 5844, 5648, 5422, 5204, 5025, 4898, 4831, },
/* LAT:  60 */ {  5391, 5385, 5419, 5486, 5574, 5669, 5756, 5820, 5851, 5840, 5783, 5687, 5564, 5433, 5312, 5214, 5145, 5109, 5105, 5132, 5187, 5272, 5388, 5534, 5701, 5870, 6019, 6126, 6173, 6152, 6070, 5943, 5795, 5651, 5529, 5440, 5391, },
/* LAT:  70 */ {  5726, 5710, 5711, 5726, 5750, 5777, 5800, 5813, 5810, 5789, 5747, 5688, 5615, 5538, 5462, 5397, 5347, 5318, 5312, 5331, 5375, 5444, 5535, 5643, 5761, 5876, 5976, 6051, 6091, 6096, 6067, 6013, 5945, 5874, 5810, 5760, 5726, },
/* LAT:  80 */ {  5788, 5772, 5759, 5748, 5739, 5730, 5720, 5708, 5692, 5672, 5649, 5623, 5594, 5566, 5540, 5519, 5504, 5499, 5503, 5517, 5543, 5577, 5620, 5668, 5718, 5766, 5809, 5844, 5869, 5882, 5885, 5879, 5865, 5847, 5827, 5807, 5788, },
/* LAT:  90 */ {  5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, 5677, },
};
