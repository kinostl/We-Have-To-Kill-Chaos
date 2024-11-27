#include "bkg_tile_info.h"
#include "ff_types.h"
#include <bankdata.h>
#include <gbs_types.h>

#pragma bank 255

void set_overworld_ptr(overworld_far_ptr *ptr, UBYTE x, UBYTE y) BANKED {
  UBYTE pos = x + (y * 16);
  switch (pos) {
  case 0:
    ptr->bank = BANK(bg_overworld_000);
    ptr->ptr = &bg_overworld_000;
    break;
  case 1:
    ptr->bank = BANK(bg_overworld_001);
    ptr->ptr = &bg_overworld_001;
    break;
  case 2:
    ptr->bank = BANK(bg_overworld_002);
    ptr->ptr = &bg_overworld_002;
    break;
  case 3:
    ptr->bank = BANK(bg_overworld_003);
    ptr->ptr = &bg_overworld_003;
    break;
  case 4:
    ptr->bank = BANK(bg_overworld_004);
    ptr->ptr = &bg_overworld_004;
    break;
  case 5:
    ptr->bank = BANK(bg_overworld_005);
    ptr->ptr = &bg_overworld_005;
    break;
  case 6:
    ptr->bank = BANK(bg_overworld_006);
    ptr->ptr = &bg_overworld_006;
    break;
  case 7:
    ptr->bank = BANK(bg_overworld_007);
    ptr->ptr = &bg_overworld_007;
    break;
  case 8:
    ptr->bank = BANK(bg_overworld_008);
    ptr->ptr = &bg_overworld_008;
    break;
  case 9:
    ptr->bank = BANK(bg_overworld_009);
    ptr->ptr = &bg_overworld_009;
    break;
  case 10:
    ptr->bank = BANK(bg_overworld_010);
    ptr->ptr = &bg_overworld_010;
    break;
  case 11:
    ptr->bank = BANK(bg_overworld_011);
    ptr->ptr = &bg_overworld_011;
    break;
  case 12:
    ptr->bank = BANK(bg_overworld_012);
    ptr->ptr = &bg_overworld_012;
    break;
  case 13:
    ptr->bank = BANK(bg_overworld_013);
    ptr->ptr = &bg_overworld_013;
    break;
  case 14:
    ptr->bank = BANK(bg_overworld_014);
    ptr->ptr = &bg_overworld_014;
    break;
  case 15:
    ptr->bank = BANK(bg_overworld_015);
    ptr->ptr = &bg_overworld_015;
    break;
  case 16:
    ptr->bank = BANK(bg_overworld_016);
    ptr->ptr = &bg_overworld_016;
    break;
  case 17:
    ptr->bank = BANK(bg_overworld_017);
    ptr->ptr = &bg_overworld_017;
    break;
  case 18:
    ptr->bank = BANK(bg_overworld_018);
    ptr->ptr = &bg_overworld_018;
    break;
  case 19:
    ptr->bank = BANK(bg_overworld_019);
    ptr->ptr = &bg_overworld_019;
    break;
  case 20:
    ptr->bank = BANK(bg_overworld_020);
    ptr->ptr = &bg_overworld_020;
    break;
  case 21:
    ptr->bank = BANK(bg_overworld_021);
    ptr->ptr = &bg_overworld_021;
    break;
  case 22:
    ptr->bank = BANK(bg_overworld_022);
    ptr->ptr = &bg_overworld_022;
    break;
  case 23:
    ptr->bank = BANK(bg_overworld_023);
    ptr->ptr = &bg_overworld_023;
    break;
  case 24:
    ptr->bank = BANK(bg_overworld_024);
    ptr->ptr = &bg_overworld_024;
    break;
  case 25:
    ptr->bank = BANK(bg_overworld_025);
    ptr->ptr = &bg_overworld_025;
    break;
  case 26:
    ptr->bank = BANK(bg_overworld_026);
    ptr->ptr = &bg_overworld_026;
    break;
  case 27:
    ptr->bank = BANK(bg_overworld_027);
    ptr->ptr = &bg_overworld_027;
    break;
  case 28:
    ptr->bank = BANK(bg_overworld_028);
    ptr->ptr = &bg_overworld_028;
    break;
  case 29:
    ptr->bank = BANK(bg_overworld_029);
    ptr->ptr = &bg_overworld_029;
    break;
  case 30:
    ptr->bank = BANK(bg_overworld_030);
    ptr->ptr = &bg_overworld_030;
    break;
  case 31:
    ptr->bank = BANK(bg_overworld_031);
    ptr->ptr = &bg_overworld_031;
    break;
  case 32:
    ptr->bank = BANK(bg_overworld_032);
    ptr->ptr = &bg_overworld_032;
    break;
  case 33:
    ptr->bank = BANK(bg_overworld_033);
    ptr->ptr = &bg_overworld_033;
    break;
  case 34:
    ptr->bank = BANK(bg_overworld_034);
    ptr->ptr = &bg_overworld_034;
    break;
  case 35:
    ptr->bank = BANK(bg_overworld_035);
    ptr->ptr = &bg_overworld_035;
    break;
  case 36:
    ptr->bank = BANK(bg_overworld_036);
    ptr->ptr = &bg_overworld_036;
    break;
  case 37:
    ptr->bank = BANK(bg_overworld_037);
    ptr->ptr = &bg_overworld_037;
    break;
  case 38:
    ptr->bank = BANK(bg_overworld_038);
    ptr->ptr = &bg_overworld_038;
    break;
  case 39:
    ptr->bank = BANK(bg_overworld_039);
    ptr->ptr = &bg_overworld_039;
    break;
  case 40:
    ptr->bank = BANK(bg_overworld_040);
    ptr->ptr = &bg_overworld_040;
    break;
  case 41:
    ptr->bank = BANK(bg_overworld_041);
    ptr->ptr = &bg_overworld_041;
    break;
  case 42:
    ptr->bank = BANK(bg_overworld_042);
    ptr->ptr = &bg_overworld_042;
    break;
  case 43:
    ptr->bank = BANK(bg_overworld_043);
    ptr->ptr = &bg_overworld_043;
    break;
  case 44:
    ptr->bank = BANK(bg_overworld_044);
    ptr->ptr = &bg_overworld_044;
    break;
  case 45:
    ptr->bank = BANK(bg_overworld_045);
    ptr->ptr = &bg_overworld_045;
    break;
  case 46:
    ptr->bank = BANK(bg_overworld_046);
    ptr->ptr = &bg_overworld_046;
    break;
  case 47:
    ptr->bank = BANK(bg_overworld_047);
    ptr->ptr = &bg_overworld_047;
    break;
  case 48:
    ptr->bank = BANK(bg_overworld_048);
    ptr->ptr = &bg_overworld_048;
    break;
  case 49:
    ptr->bank = BANK(bg_overworld_049);
    ptr->ptr = &bg_overworld_049;
    break;
  case 50:
    ptr->bank = BANK(bg_overworld_050);
    ptr->ptr = &bg_overworld_050;
    break;
  case 51:
    ptr->bank = BANK(bg_overworld_051);
    ptr->ptr = &bg_overworld_051;
    break;
  case 52:
    ptr->bank = BANK(bg_overworld_052);
    ptr->ptr = &bg_overworld_052;
    break;
  case 53:
    ptr->bank = BANK(bg_overworld_053);
    ptr->ptr = &bg_overworld_053;
    break;
  case 54:
    ptr->bank = BANK(bg_overworld_054);
    ptr->ptr = &bg_overworld_054;
    break;
  case 55:
    ptr->bank = BANK(bg_overworld_055);
    ptr->ptr = &bg_overworld_055;
    break;
  case 56:
    ptr->bank = BANK(bg_overworld_056);
    ptr->ptr = &bg_overworld_056;
    break;
  case 57:
    ptr->bank = BANK(bg_overworld_057);
    ptr->ptr = &bg_overworld_057;
    break;
  case 58:
    ptr->bank = BANK(bg_overworld_058);
    ptr->ptr = &bg_overworld_058;
    break;
  case 59:
    ptr->bank = BANK(bg_overworld_059);
    ptr->ptr = &bg_overworld_059;
    break;
  case 60:
    ptr->bank = BANK(bg_overworld_060);
    ptr->ptr = &bg_overworld_060;
    break;
  case 61:
    ptr->bank = BANK(bg_overworld_061);
    ptr->ptr = &bg_overworld_061;
    break;
  case 62:
    ptr->bank = BANK(bg_overworld_062);
    ptr->ptr = &bg_overworld_062;
    break;
  case 63:
    ptr->bank = BANK(bg_overworld_063);
    ptr->ptr = &bg_overworld_063;
    break;
  case 64:
    ptr->bank = BANK(bg_overworld_064);
    ptr->ptr = &bg_overworld_064;
    break;
  case 65:
    ptr->bank = BANK(bg_overworld_065);
    ptr->ptr = &bg_overworld_065;
    break;
  case 66:
    ptr->bank = BANK(bg_overworld_066);
    ptr->ptr = &bg_overworld_066;
    break;
  case 67:
    ptr->bank = BANK(bg_overworld_067);
    ptr->ptr = &bg_overworld_067;
    break;
  case 68:
    ptr->bank = BANK(bg_overworld_068);
    ptr->ptr = &bg_overworld_068;
    break;
  case 69:
    ptr->bank = BANK(bg_overworld_069);
    ptr->ptr = &bg_overworld_069;
    break;
  case 70:
    ptr->bank = BANK(bg_overworld_070);
    ptr->ptr = &bg_overworld_070;
    break;
  case 71:
    ptr->bank = BANK(bg_overworld_071);
    ptr->ptr = &bg_overworld_071;
    break;
  case 72:
    ptr->bank = BANK(bg_overworld_072);
    ptr->ptr = &bg_overworld_072;
    break;
  case 73:
    ptr->bank = BANK(bg_overworld_073);
    ptr->ptr = &bg_overworld_073;
    break;
  case 74:
    ptr->bank = BANK(bg_overworld_074);
    ptr->ptr = &bg_overworld_074;
    break;
  case 75:
    ptr->bank = BANK(bg_overworld_075);
    ptr->ptr = &bg_overworld_075;
    break;
  case 76:
    ptr->bank = BANK(bg_overworld_076);
    ptr->ptr = &bg_overworld_076;
    break;
  case 77:
    ptr->bank = BANK(bg_overworld_077);
    ptr->ptr = &bg_overworld_077;
    break;
  case 78:
    ptr->bank = BANK(bg_overworld_078);
    ptr->ptr = &bg_overworld_078;
    break;
  case 79:
    ptr->bank = BANK(bg_overworld_079);
    ptr->ptr = &bg_overworld_079;
    break;
  case 80:
    ptr->bank = BANK(bg_overworld_080);
    ptr->ptr = &bg_overworld_080;
    break;
  case 81:
    ptr->bank = BANK(bg_overworld_081);
    ptr->ptr = &bg_overworld_081;
    break;
  case 82:
    ptr->bank = BANK(bg_overworld_082);
    ptr->ptr = &bg_overworld_082;
    break;
  case 83:
    ptr->bank = BANK(bg_overworld_083);
    ptr->ptr = &bg_overworld_083;
    break;
  case 84:
    ptr->bank = BANK(bg_overworld_084);
    ptr->ptr = &bg_overworld_084;
    break;
  case 85:
    ptr->bank = BANK(bg_overworld_085);
    ptr->ptr = &bg_overworld_085;
    break;
  case 86:
    ptr->bank = BANK(bg_overworld_086);
    ptr->ptr = &bg_overworld_086;
    break;
  case 87:
    ptr->bank = BANK(bg_overworld_087);
    ptr->ptr = &bg_overworld_087;
    break;
  case 88:
    ptr->bank = BANK(bg_overworld_088);
    ptr->ptr = &bg_overworld_088;
    break;
  case 89:
    ptr->bank = BANK(bg_overworld_089);
    ptr->ptr = &bg_overworld_089;
    break;
  case 90:
    ptr->bank = BANK(bg_overworld_090);
    ptr->ptr = &bg_overworld_090;
    break;
  case 91:
    ptr->bank = BANK(bg_overworld_091);
    ptr->ptr = &bg_overworld_091;
    break;
  case 92:
    ptr->bank = BANK(bg_overworld_092);
    ptr->ptr = &bg_overworld_092;
    break;
  case 93:
    ptr->bank = BANK(bg_overworld_093);
    ptr->ptr = &bg_overworld_093;
    break;
  case 94:
    ptr->bank = BANK(bg_overworld_094);
    ptr->ptr = &bg_overworld_094;
    break;
  case 95:
    ptr->bank = BANK(bg_overworld_095);
    ptr->ptr = &bg_overworld_095;
    break;
  case 96:
    ptr->bank = BANK(bg_overworld_096);
    ptr->ptr = &bg_overworld_096;
    break;
  case 97:
    ptr->bank = BANK(bg_overworld_097);
    ptr->ptr = &bg_overworld_097;
    break;
  case 98:
    ptr->bank = BANK(bg_overworld_098);
    ptr->ptr = &bg_overworld_098;
    break;
  case 99:
    ptr->bank = BANK(bg_overworld_099);
    ptr->ptr = &bg_overworld_099;
    break;
  case 100:
    ptr->bank = BANK(bg_overworld_100);
    ptr->ptr = &bg_overworld_100;
    break;
  case 101:
    ptr->bank = BANK(bg_overworld_101);
    ptr->ptr = &bg_overworld_101;
    break;
  case 102:
    ptr->bank = BANK(bg_overworld_102);
    ptr->ptr = &bg_overworld_102;
    break;
  case 103:
    ptr->bank = BANK(bg_overworld_103);
    ptr->ptr = &bg_overworld_103;
    break;
  case 104:
    ptr->bank = BANK(bg_overworld_104);
    ptr->ptr = &bg_overworld_104;
    break;
  case 105:
    ptr->bank = BANK(bg_overworld_105);
    ptr->ptr = &bg_overworld_105;
    break;
  case 106:
    ptr->bank = BANK(bg_overworld_106);
    ptr->ptr = &bg_overworld_106;
    break;
  case 107:
    ptr->bank = BANK(bg_overworld_107);
    ptr->ptr = &bg_overworld_107;
    break;
  case 108:
    ptr->bank = BANK(bg_overworld_108);
    ptr->ptr = &bg_overworld_108;
    break;
  case 109:
    ptr->bank = BANK(bg_overworld_109);
    ptr->ptr = &bg_overworld_109;
    break;
  case 110:
    ptr->bank = BANK(bg_overworld_110);
    ptr->ptr = &bg_overworld_110;
    break;
  case 111:
    ptr->bank = BANK(bg_overworld_111);
    ptr->ptr = &bg_overworld_111;
    break;
  case 112:
    ptr->bank = BANK(bg_overworld_112);
    ptr->ptr = &bg_overworld_112;
    break;
  case 113:
    ptr->bank = BANK(bg_overworld_113);
    ptr->ptr = &bg_overworld_113;
    break;
  case 114:
    ptr->bank = BANK(bg_overworld_114);
    ptr->ptr = &bg_overworld_114;
    break;
  case 115:
    ptr->bank = BANK(bg_overworld_115);
    ptr->ptr = &bg_overworld_115;
    break;
  case 116:
    ptr->bank = BANK(bg_overworld_116);
    ptr->ptr = &bg_overworld_116;
    break;
  case 117:
    ptr->bank = BANK(bg_overworld_117);
    ptr->ptr = &bg_overworld_117;
    break;
  case 118:
    ptr->bank = BANK(bg_overworld_118);
    ptr->ptr = &bg_overworld_118;
    break;
  case 119:
    ptr->bank = BANK(bg_overworld_119);
    ptr->ptr = &bg_overworld_119;
    break;
  case 120:
    ptr->bank = BANK(bg_overworld_120);
    ptr->ptr = &bg_overworld_120;
    break;
  case 121:
    ptr->bank = BANK(bg_overworld_121);
    ptr->ptr = &bg_overworld_121;
    break;
  case 122:
    ptr->bank = BANK(bg_overworld_122);
    ptr->ptr = &bg_overworld_122;
    break;
  case 123:
    ptr->bank = BANK(bg_overworld_123);
    ptr->ptr = &bg_overworld_123;
    break;
  case 124:
    ptr->bank = BANK(bg_overworld_124);
    ptr->ptr = &bg_overworld_124;
    break;
  case 125:
    ptr->bank = BANK(bg_overworld_125);
    ptr->ptr = &bg_overworld_125;
    break;
  case 126:
    ptr->bank = BANK(bg_overworld_126);
    ptr->ptr = &bg_overworld_126;
    break;
  case 127:
    ptr->bank = BANK(bg_overworld_127);
    ptr->ptr = &bg_overworld_127;
    break;
  case 128:
    ptr->bank = BANK(bg_overworld_128);
    ptr->ptr = &bg_overworld_128;
    break;
  case 129:
    ptr->bank = BANK(bg_overworld_129);
    ptr->ptr = &bg_overworld_129;
    break;
  case 130:
    ptr->bank = BANK(bg_overworld_130);
    ptr->ptr = &bg_overworld_130;
    break;
  case 131:
    ptr->bank = BANK(bg_overworld_131);
    ptr->ptr = &bg_overworld_131;
    break;
  case 132:
    ptr->bank = BANK(bg_overworld_132);
    ptr->ptr = &bg_overworld_132;
    break;
  case 133:
    ptr->bank = BANK(bg_overworld_133);
    ptr->ptr = &bg_overworld_133;
    break;
  case 134:
    ptr->bank = BANK(bg_overworld_134);
    ptr->ptr = &bg_overworld_134;
    break;
  case 135:
    ptr->bank = BANK(bg_overworld_135);
    ptr->ptr = &bg_overworld_135;
    break;
  case 136:
    ptr->bank = BANK(bg_overworld_136);
    ptr->ptr = &bg_overworld_136;
    break;
  case 137:
    ptr->bank = BANK(bg_overworld_137);
    ptr->ptr = &bg_overworld_137;
    break;
  case 138:
    ptr->bank = BANK(bg_overworld_138);
    ptr->ptr = &bg_overworld_138;
    break;
  case 139:
    ptr->bank = BANK(bg_overworld_139);
    ptr->ptr = &bg_overworld_139;
    break;
  case 140:
    ptr->bank = BANK(bg_overworld_140);
    ptr->ptr = &bg_overworld_140;
    break;
  case 141:
    ptr->bank = BANK(bg_overworld_141);
    ptr->ptr = &bg_overworld_141;
    break;
  case 142:
    ptr->bank = BANK(bg_overworld_142);
    ptr->ptr = &bg_overworld_142;
    break;
  case 143:
    ptr->bank = BANK(bg_overworld_143);
    ptr->ptr = &bg_overworld_143;
    break;
  case 144:
    ptr->bank = BANK(bg_overworld_144);
    ptr->ptr = &bg_overworld_144;
    break;
  case 145:
    ptr->bank = BANK(bg_overworld_145);
    ptr->ptr = &bg_overworld_145;
    break;
  case 146:
    ptr->bank = BANK(bg_overworld_146);
    ptr->ptr = &bg_overworld_146;
    break;
  case 147:
    ptr->bank = BANK(bg_overworld_147);
    ptr->ptr = &bg_overworld_147;
    break;
  case 148:
    ptr->bank = BANK(bg_overworld_148);
    ptr->ptr = &bg_overworld_148;
    break;
  case 149:
    ptr->bank = BANK(bg_overworld_149);
    ptr->ptr = &bg_overworld_149;
    break;
  case 150:
    ptr->bank = BANK(bg_overworld_150);
    ptr->ptr = &bg_overworld_150;
    break;
  case 151:
    ptr->bank = BANK(bg_overworld_151);
    ptr->ptr = &bg_overworld_151;
    break;
  case 152:
    ptr->bank = BANK(bg_overworld_152);
    ptr->ptr = &bg_overworld_152;
    break;
  case 153:
    ptr->bank = BANK(bg_overworld_153);
    ptr->ptr = &bg_overworld_153;
    break;
  case 154:
    ptr->bank = BANK(bg_overworld_154);
    ptr->ptr = &bg_overworld_154;
    break;
  case 155:
    ptr->bank = BANK(bg_overworld_155);
    ptr->ptr = &bg_overworld_155;
    break;
  case 156:
    ptr->bank = BANK(bg_overworld_156);
    ptr->ptr = &bg_overworld_156;
    break;
  case 157:
    ptr->bank = BANK(bg_overworld_157);
    ptr->ptr = &bg_overworld_157;
    break;
  case 158:
    ptr->bank = BANK(bg_overworld_158);
    ptr->ptr = &bg_overworld_158;
    break;
  case 159:
    ptr->bank = BANK(bg_overworld_159);
    ptr->ptr = &bg_overworld_159;
    break;
  case 160:
    ptr->bank = BANK(bg_overworld_160);
    ptr->ptr = &bg_overworld_160;
    break;
  case 161:
    ptr->bank = BANK(bg_overworld_161);
    ptr->ptr = &bg_overworld_161;
    break;
  case 162:
    ptr->bank = BANK(bg_overworld_162);
    ptr->ptr = &bg_overworld_162;
    break;
  case 163:
    ptr->bank = BANK(bg_overworld_163);
    ptr->ptr = &bg_overworld_163;
    break;
  case 164:
    ptr->bank = BANK(bg_overworld_164);
    ptr->ptr = &bg_overworld_164;
    break;
  case 165:
    ptr->bank = BANK(bg_overworld_165);
    ptr->ptr = &bg_overworld_165;
    break;
  case 166:
    ptr->bank = BANK(bg_overworld_166);
    ptr->ptr = &bg_overworld_166;
    break;
  case 167:
    ptr->bank = BANK(bg_overworld_167);
    ptr->ptr = &bg_overworld_167;
    break;
  case 168:
    ptr->bank = BANK(bg_overworld_168);
    ptr->ptr = &bg_overworld_168;
    break;
  case 169:
    ptr->bank = BANK(bg_overworld_169);
    ptr->ptr = &bg_overworld_169;
    break;
  case 170:
    ptr->bank = BANK(bg_overworld_170);
    ptr->ptr = &bg_overworld_170;
    break;
  case 171:
    ptr->bank = BANK(bg_overworld_171);
    ptr->ptr = &bg_overworld_171;
    break;
  case 172:
    ptr->bank = BANK(bg_overworld_172);
    ptr->ptr = &bg_overworld_172;
    break;
  case 173:
    ptr->bank = BANK(bg_overworld_173);
    ptr->ptr = &bg_overworld_173;
    break;
  case 174:
    ptr->bank = BANK(bg_overworld_174);
    ptr->ptr = &bg_overworld_174;
    break;
  case 175:
    ptr->bank = BANK(bg_overworld_175);
    ptr->ptr = &bg_overworld_175;
    break;
  case 176:
    ptr->bank = BANK(bg_overworld_176);
    ptr->ptr = &bg_overworld_176;
    break;
  case 177:
    ptr->bank = BANK(bg_overworld_177);
    ptr->ptr = &bg_overworld_177;
    break;
  case 178:
    ptr->bank = BANK(bg_overworld_178);
    ptr->ptr = &bg_overworld_178;
    break;
  case 179:
    ptr->bank = BANK(bg_overworld_179);
    ptr->ptr = &bg_overworld_179;
    break;
  case 180:
    ptr->bank = BANK(bg_overworld_180);
    ptr->ptr = &bg_overworld_180;
    break;
  case 181:
    ptr->bank = BANK(bg_overworld_181);
    ptr->ptr = &bg_overworld_181;
    break;
  case 182:
    ptr->bank = BANK(bg_overworld_182);
    ptr->ptr = &bg_overworld_182;
    break;
  case 183:
    ptr->bank = BANK(bg_overworld_183);
    ptr->ptr = &bg_overworld_183;
    break;
  case 184:
    ptr->bank = BANK(bg_overworld_184);
    ptr->ptr = &bg_overworld_184;
    break;
  case 185:
    ptr->bank = BANK(bg_overworld_185);
    ptr->ptr = &bg_overworld_185;
    break;
  case 186:
    ptr->bank = BANK(bg_overworld_186);
    ptr->ptr = &bg_overworld_186;
    break;
  case 187:
    ptr->bank = BANK(bg_overworld_187);
    ptr->ptr = &bg_overworld_187;
    break;
  case 188:
    ptr->bank = BANK(bg_overworld_188);
    ptr->ptr = &bg_overworld_188;
    break;
  case 189:
    ptr->bank = BANK(bg_overworld_189);
    ptr->ptr = &bg_overworld_189;
    break;
  case 190:
    ptr->bank = BANK(bg_overworld_190);
    ptr->ptr = &bg_overworld_190;
    break;
  case 191:
    ptr->bank = BANK(bg_overworld_191);
    ptr->ptr = &bg_overworld_191;
    break;
  case 192:
    ptr->bank = BANK(bg_overworld_192);
    ptr->ptr = &bg_overworld_192;
    break;
  case 193:
    ptr->bank = BANK(bg_overworld_193);
    ptr->ptr = &bg_overworld_193;
    break;
  case 194:
    ptr->bank = BANK(bg_overworld_194);
    ptr->ptr = &bg_overworld_194;
    break;
  case 195:
    ptr->bank = BANK(bg_overworld_195);
    ptr->ptr = &bg_overworld_195;
    break;
  case 196:
    ptr->bank = BANK(bg_overworld_196);
    ptr->ptr = &bg_overworld_196;
    break;
  case 197:
    ptr->bank = BANK(bg_overworld_197);
    ptr->ptr = &bg_overworld_197;
    break;
  case 198:
    ptr->bank = BANK(bg_overworld_198);
    ptr->ptr = &bg_overworld_198;
    break;
  case 199:
    ptr->bank = BANK(bg_overworld_199);
    ptr->ptr = &bg_overworld_199;
    break;
  case 200:
    ptr->bank = BANK(bg_overworld_200);
    ptr->ptr = &bg_overworld_200;
    break;
  case 201:
    ptr->bank = BANK(bg_overworld_201);
    ptr->ptr = &bg_overworld_201;
    break;
  case 202:
    ptr->bank = BANK(bg_overworld_202);
    ptr->ptr = &bg_overworld_202;
    break;
  case 203:
    ptr->bank = BANK(bg_overworld_203);
    ptr->ptr = &bg_overworld_203;
    break;
  case 204:
    ptr->bank = BANK(bg_overworld_204);
    ptr->ptr = &bg_overworld_204;
    break;
  case 205:
    ptr->bank = BANK(bg_overworld_205);
    ptr->ptr = &bg_overworld_205;
    break;
  case 206:
    ptr->bank = BANK(bg_overworld_206);
    ptr->ptr = &bg_overworld_206;
    break;
  case 207:
    ptr->bank = BANK(bg_overworld_207);
    ptr->ptr = &bg_overworld_207;
    break;
  case 208:
    ptr->bank = BANK(bg_overworld_208);
    ptr->ptr = &bg_overworld_208;
    break;
  case 209:
    ptr->bank = BANK(bg_overworld_209);
    ptr->ptr = &bg_overworld_209;
    break;
  case 210:
    ptr->bank = BANK(bg_overworld_210);
    ptr->ptr = &bg_overworld_210;
    break;
  case 211:
    ptr->bank = BANK(bg_overworld_211);
    ptr->ptr = &bg_overworld_211;
    break;
  case 212:
    ptr->bank = BANK(bg_overworld_212);
    ptr->ptr = &bg_overworld_212;
    break;
  case 213:
    ptr->bank = BANK(bg_overworld_213);
    ptr->ptr = &bg_overworld_213;
    break;
  case 214:
    ptr->bank = BANK(bg_overworld_214);
    ptr->ptr = &bg_overworld_214;
    break;
  case 215:
    ptr->bank = BANK(bg_overworld_215);
    ptr->ptr = &bg_overworld_215;
    break;
  case 216:
    ptr->bank = BANK(bg_overworld_216);
    ptr->ptr = &bg_overworld_216;
    break;
  case 217:
    ptr->bank = BANK(bg_overworld_217);
    ptr->ptr = &bg_overworld_217;
    break;
  case 218:
    ptr->bank = BANK(bg_overworld_218);
    ptr->ptr = &bg_overworld_218;
    break;
  case 219:
    ptr->bank = BANK(bg_overworld_219);
    ptr->ptr = &bg_overworld_219;
    break;
  case 220:
    ptr->bank = BANK(bg_overworld_220);
    ptr->ptr = &bg_overworld_220;
    break;
  case 221:
    ptr->bank = BANK(bg_overworld_221);
    ptr->ptr = &bg_overworld_221;
    break;
  case 222:
    ptr->bank = BANK(bg_overworld_222);
    ptr->ptr = &bg_overworld_222;
    break;
  case 223:
    ptr->bank = BANK(bg_overworld_223);
    ptr->ptr = &bg_overworld_223;
    break;
  case 224:
    ptr->bank = BANK(bg_overworld_224);
    ptr->ptr = &bg_overworld_224;
    break;
  case 225:
    ptr->bank = BANK(bg_overworld_225);
    ptr->ptr = &bg_overworld_225;
    break;
  case 226:
    ptr->bank = BANK(bg_overworld_226);
    ptr->ptr = &bg_overworld_226;
    break;
  case 227:
    ptr->bank = BANK(bg_overworld_227);
    ptr->ptr = &bg_overworld_227;
    break;
  case 228:
    ptr->bank = BANK(bg_overworld_228);
    ptr->ptr = &bg_overworld_228;
    break;
  case 229:
    ptr->bank = BANK(bg_overworld_229);
    ptr->ptr = &bg_overworld_229;
    break;
  case 230:
    ptr->bank = BANK(bg_overworld_230);
    ptr->ptr = &bg_overworld_230;
    break;
  case 231:
    ptr->bank = BANK(bg_overworld_231);
    ptr->ptr = &bg_overworld_231;
    break;
  case 232:
    ptr->bank = BANK(bg_overworld_232);
    ptr->ptr = &bg_overworld_232;
    break;
  case 233:
    ptr->bank = BANK(bg_overworld_233);
    ptr->ptr = &bg_overworld_233;
    break;
  case 234:
    ptr->bank = BANK(bg_overworld_234);
    ptr->ptr = &bg_overworld_234;
    break;
  case 235:
    ptr->bank = BANK(bg_overworld_235);
    ptr->ptr = &bg_overworld_235;
    break;
  case 236:
    ptr->bank = BANK(bg_overworld_236);
    ptr->ptr = &bg_overworld_236;
    break;
  case 237:
    ptr->bank = BANK(bg_overworld_237);
    ptr->ptr = &bg_overworld_237;
    break;
  case 238:
    ptr->bank = BANK(bg_overworld_238);
    ptr->ptr = &bg_overworld_238;
    break;
  case 239:
    ptr->bank = BANK(bg_overworld_239);
    ptr->ptr = &bg_overworld_239;
    break;
  case 240:
    ptr->bank = BANK(bg_overworld_240);
    ptr->ptr = &bg_overworld_240;
    break;
  case 241:
    ptr->bank = BANK(bg_overworld_241);
    ptr->ptr = &bg_overworld_241;
    break;
  case 242:
    ptr->bank = BANK(bg_overworld_242);
    ptr->ptr = &bg_overworld_242;
    break;
  case 243:
    ptr->bank = BANK(bg_overworld_243);
    ptr->ptr = &bg_overworld_243;
    break;
  case 244:
    ptr->bank = BANK(bg_overworld_244);
    ptr->ptr = &bg_overworld_244;
    break;
  case 245:
    ptr->bank = BANK(bg_overworld_245);
    ptr->ptr = &bg_overworld_245;
    break;
  case 246:
    ptr->bank = BANK(bg_overworld_246);
    ptr->ptr = &bg_overworld_246;
    break;
  case 247:
    ptr->bank = BANK(bg_overworld_247);
    ptr->ptr = &bg_overworld_247;
    break;
  case 248:
    ptr->bank = BANK(bg_overworld_248);
    ptr->ptr = &bg_overworld_248;
    break;
  case 249:
    ptr->bank = BANK(bg_overworld_249);
    ptr->ptr = &bg_overworld_249;
    break;
  case 250:
    ptr->bank = BANK(bg_overworld_250);
    ptr->ptr = &bg_overworld_250;
    break;
  case 251:
    ptr->bank = BANK(bg_overworld_251);
    ptr->ptr = &bg_overworld_251;
    break;
  case 252:
    ptr->bank = BANK(bg_overworld_252);
    ptr->ptr = &bg_overworld_252;
    break;
  case 253:
    ptr->bank = BANK(bg_overworld_253);
    ptr->ptr = &bg_overworld_253;
    break;
  case 254:
    ptr->bank = BANK(bg_overworld_254);
    ptr->ptr = &bg_overworld_254;
    break;
  case 255:
    ptr->bank = BANK(bg_overworld_255);
    ptr->ptr = &bg_overworld_255;
    break;
  }
}