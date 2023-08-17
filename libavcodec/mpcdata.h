/*
 * Musepack decoder
 * Copyright (c) 2006 Konstantin Shishkov
 *
 * This file is part of FFmpreg.
 *
 * FFmpreg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpreg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpreg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_MPCDATA_H
#define AVCODEC_MPCDATA_H

static const float mpc_CC[18+1] = {
    111.285962475327f, // 32768/2/255*sqrt(3)
    65536.0000 /* this value is never used */,
    21845.3333, 13107.2000, 9362.2857, 7281.7778, 4369.0667, 2114.0645,
    1040.2539, 516.0315, 257.0039, 128.2505, 64.0626, 32.0156, 16.0039, 8.0010,
    4.0002, 2.0001, 1.0000
};

static const float mpc_SCF[256] = {
    307.330047607421875000, 255.999984741210937500, 213.243041992187500000, 177.627334594726562500,
    147.960128784179687500, 123.247924804687500000, 102.663139343261718750, 85.516410827636718750,
    71.233520507812500000, 59.336143493652343750, 49.425861358642578125, 41.170787811279296875,
    34.294471740722656250, 28.566631317138671875, 23.795452117919921875, 19.821151733398437500,
    16.510635375976562500, 13.753040313720703125, 11.456016540527343750, 9.542640686035156250,
    7.948835372924804688, 6.621226310729980469, 5.515353679656982422, 4.594182968139648438,
    3.826865673065185547, 3.187705039978027344, 2.655296564102172852, 2.211810588836669922,
    1.842395424842834473, 1.534679770469665527, 1.278358578681945801, 1.064847946166992188,
    0.886997759342193604, 0.738851964473724365, 0.615449428558349609, 0.512657463550567627,
    0.427033752202987671, 0.355710864067077637, 0.296300262212753296, 0.246812388300895691,
    0.205589950084686279, 0.171252459287643433, 0.142649993300437927, 0.118824683129787445,
    0.098978661000728607, 0.082447312772274017, 0.068677015602588654, 0.057206626981496811,
    0.047652013599872589, 0.039693206548690796, 0.033063672482967377, 0.027541399002075195,
    0.022941453382372856, 0.019109787419438362, 0.015918083488941193, 0.013259455561637878,
    0.011044870130717754, 0.009200163185596466, 0.007663558237254620, 0.006383595988154411,
    0.005317411851137877, 0.004429301247000694, 0.003689522389322519, 0.003073300700634718,
    0.002560000168159604, 0.002132430672645569, 0.001776273478753865, 0.001479601487517357,
    0.001232479466125369, 0.001026631565764546, 0.000855164253152907, 0.000712335284333676,
    0.000593361502978951, 0.000494258652906865, 0.000411707907915115, 0.000342944724252447,
    0.000285666319541633, 0.000237954518524930, 0.000198211506358348, 0.000165106350323185,
    0.000137530398205854, 0.000114560163638089, 0.000095426403277088, 0.000079488345363643,
    0.000066212254751008, 0.000055153526773211, 0.000045941822463647, 0.000038268648495432,
    0.000031877043511486, 0.000026552961571724, 0.000022118103515822, 0.000018423952496960,
    0.000015346795407822, 0.000012783583770215, 0.000010648477655195, 0.000008869976227288,
    0.000007388518497464, 0.000006154492893984, 0.000005126573796588, 0.000004270336830814,
    0.000003557107902452, 0.000002963002089018, 0.000002468123511790, 0.000002055899130937,
    0.000001712524181130, 0.000001426499579793, 0.000001188246528727, 0.000000989786371974,
    0.000000824472920158, 0.000000686770022185, 0.000000572066142013, 0.000000476520028769,
    0.000000396931966407, 0.000000330636652279, 0.000000275413924555, 0.000000229414467867,
    0.000000191097811353, 0.000000159180785886, 0.000000132594522029, 0.000000110448674207,
    0.000000092001613439, 0.000000076635565449, 0.000000063835940978, 0.000000053174105119,
    0.000000044293003043, 0.000000036895215771, 0.000000030733001921, 0.000000025599996789,
    0.000000021324305018, 3689522167600.270019531250000000, 3073300627835.926757812500000000, 2560000000000.002929687500000000,
    2132430501800.519042968750000000, 1776273376956.721923828125000000, 1479601378343.250244140625000000, 1232479339720.794189453125000000,
    1026631459710.774291992187500000, 855164155779.391845703125000000, 712335206965.024780273437500000, 593361454233.829101562500000000,
    494258618594.112609863281250000, 411707872682.763122558593750000, 342944697476.612365722656250000, 285666302081.983886718750000000,
    237954506209.446411132812500000, 198211502766.368713378906250000, 165106349338.563323974609375000, 137530396629.095306396484375000,
    114560161209.611633300781250000, 95426399240.062576293945312500, 79488345475.196502685546875000, 66212254855.064872741699218750,
    55153528064.816276550292968750, 45941822471.611343383789062500, 38268649822.956413269042968750, 31877045369.216873168945312500,
    26552962442.420688629150390625, 22118104306.789615631103515625, 18423953228.829509735107421875, 15346796808.164905548095703125,
    12783585007.291271209716796875, 10648479137.463939666748046875, 8869977230.669750213623046875, 7388519530.061036109924316406,
    6154493909.785535812377929688, 5126574428.270387649536132812, 4270337375.232155323028564453, 3557108465.595236301422119141,
    2963002574.315670013427734375, 2468123854.056322574615478516, 2055899448.676229715347290039, 1712524489.450022459030151367,
    1426499787.649837732315063477, 1188246741.404872417449951172, 989786560.561257958412170410, 824473067.192597866058349609,
    686770123.591610312461853027, 572066234.090648531913757324, 476520111.962911486625671387, 396932039.637152194976806641,
    330636714.243810534477233887, 275413990.026798009872436523, 229414528.498330980539321899, 191097866.455478429794311523,
    159180827.835415601730346680, 132594551.788319095969200134, 110448697.892960876226425171, 92001629.793398514389991760,
    76635578.744844585657119751, 63835955.327594503760337830, 53174116.504741288721561432, 44293010.914454914629459381,
    36895221.676002673804759979, 30733006.278359245508909225, 25600000.000000011175870895, 21324305.018005173653364182,
    17762733.769567202776670456, 14796013.783432489261031151, 12324793.397207930684089661, 10266314.597107734531164169,
    8551641.557793911546468735, 7123352.069650243036448956, 5933614.542338287457823753, 4942586.185941123403608799,
    4117078.726827629376202822, 3429446.974766122177243233, 2856663.020819837693125010, 2379545.062094463035464287,
    1982115.027663686312735081, 1651063.493385632522404194, 1375303.966290952404960990, 1145601.612096115713939071,
    954263.992400625254958868, 794883.454751964658498764, 662122.548550648498348892, 551535.280648162588477135,
    459418.224716113239992410, 382686.498229563992936164, 318770.453692168579436839, 265529.624424206791445613,
    221181.043067896069260314, 184239.532288295013131574, 153467.968081648985389620, 127835.850072912653558888,
    106484.791374639346031472, 88699.772306697457679547, 73885.195300610314006917, 61544.939097855312866159,
    51265.744282703839417081, 42703.373752321524079889, 35571.084655952341563534, 29630.025743156678800005,
    24681.238540563208516687, 20558.994486762283486314, 17125.244894500214286381, 14264.997876498367986642,
    11882.467414048716818797, 9897.865605612574654515, 8244.730671925974093028, 6867.701235916098994494,
    5720.662340906482313585, 4765.201119629112326948, 3969.320396371519564127, 3306.367142438103201130,
    2754.139900267978191550, 2294.145284983308101801, 1910.978664554782881169, 1591.808278354154936096,
    1325.945517883190177599, 1104.486978929608085309, 920.016297933984674273, 766.355787448445425980,
    638.359553275944676898, 531.741165047412550848, 442.930109144548907807, 368.952216760026544762,
};

#endif /* AVCODEC_MPCDATA_H */
