/*
 * Copyright (c) 1997-1999, 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Mar 24 02:06:37 EST 2003 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: /homee/stevenj/cvs/fftw/gensrc/genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -notwiddleinv 13 */

/*
 * This function contains 176 FP additions, 68 FP multiplications,
 * (or, 138 additions, 30 multiplications, 38 fused multiply/add),
 * 50 stack variables, and 52 memory accesses
 */
static const fftw_real K1_732050807 =
FFTW_KONST(+1.732050807568877293527446341505872366942805254);
static const fftw_real K156891391 =
FFTW_KONST(+0.156891391051584611046832726756003269660212636);
static const fftw_real K256247671 =
FFTW_KONST(+0.256247671582936600958684654061725059144125175);
static const fftw_real K300238635 =
FFTW_KONST(+0.300238635966332641462884626667381504676006424);
static const fftw_real K011599105 =
FFTW_KONST(+0.011599105605768290721655456654083252189827041);
static const fftw_real K174138601 =
FFTW_KONST(+0.174138601152135905005660794929264742616964676);
static const fftw_real K575140729 =
FFTW_KONST(+0.575140729474003121368385547455453388461001608);
static const fftw_real K2_000000000 =
FFTW_KONST(+2.000000000000000000000000000000000000000000000);
static const fftw_real K083333333 =
FFTW_KONST(+0.083333333333333333333333333333333333333333333);
static const fftw_real K075902986 =
FFTW_KONST(+0.075902986037193865983102897245103540356428373);
static const fftw_real K251768516 =
FFTW_KONST(+0.251768516431883313623436926934233488546674281);
static const fftw_real K258260390 =
FFTW_KONST(+0.258260390311744861420450644284508567852516811);
static const fftw_real K132983124 =
FFTW_KONST(+0.132983124607418643793760531921092974399165133);
static const fftw_real K503537032 =
FFTW_KONST(+0.503537032863766627246873853868466977093348562);
static const fftw_real K113854479 =
FFTW_KONST(+0.113854479055790798974654345867655310534642560);
static const fftw_real K265966249 =
FFTW_KONST(+0.265966249214837287587521063842185948798330267);
static const fftw_real K387390585 =
FFTW_KONST(+0.387390585467617292130675966426762851778775217);
static const fftw_real K866025403 =
FFTW_KONST(+0.866025403784438646763723170752936183471402627);
static const fftw_real K300462606 =
FFTW_KONST(+0.300462606288665774426601772289207995520941381);
static const fftw_real K500000000 =
FFTW_KONST(+0.500000000000000000000000000000000000000000000);

/*
 * Generator Id's : 
 * $Id: fni_13.c,v 1.1 2008/10/17 06:13:18 scuri Exp $
 * $Id: fni_13.c,v 1.1 2008/10/17 06:13:18 scuri Exp $
 * $Id: fni_13.c,v 1.1 2008/10/17 06:13:18 scuri Exp $
 */

void fftwi_no_twiddle_13(const fftw_complex *input, fftw_complex *output,
			 int istride, int ostride)
{
     fftw_real tmp1;
     fftw_real tmp146;
     fftw_real tmp113;
     fftw_real tmp24;
     fftw_real tmp38;
     fftw_real tmp36;
     fftw_real tmp41;
     fftw_real tmp116;
     fftw_real tmp120;
     fftw_real tmp125;
     fftw_real tmp31;
     fftw_real tmp40;
     fftw_real tmp123;
     fftw_real tmp126;
     fftw_real tmp56;
     fftw_real tmp80;
     fftw_real tmp82;
     fftw_real tmp137;
     fftw_real tmp144;
     fftw_real tmp67;
     fftw_real tmp141;
     fftw_real tmp147;
     fftw_real tmp134;
     fftw_real tmp143;
     fftw_real tmp75;
     fftw_real tmp83;
     ASSERT_ALIGNED_DOUBLE;
     tmp1 = c_re(input[0]);
     tmp146 = c_im(input[0]);
     {
	  fftw_real tmp15;
	  fftw_real tmp114;
	  fftw_real tmp18;
	  fftw_real tmp26;
	  fftw_real tmp21;
	  fftw_real tmp25;
	  fftw_real tmp22;
	  fftw_real tmp115;
	  fftw_real tmp6;
	  fftw_real tmp32;
	  fftw_real tmp28;
	  fftw_real tmp11;
	  fftw_real tmp33;
	  fftw_real tmp29;
	  fftw_real tmp13;
	  fftw_real tmp14;
	  fftw_real tmp118;
	  fftw_real tmp119;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp13 = c_re(input[8 * istride]);
	  tmp14 = c_re(input[5 * istride]);
	  tmp15 = tmp13 + tmp14;
	  tmp114 = tmp13 - tmp14;
	  {
	       fftw_real tmp16;
	       fftw_real tmp17;
	       fftw_real tmp19;
	       fftw_real tmp20;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp16 = c_re(input[6 * istride]);
	       tmp17 = c_re(input[11 * istride]);
	       tmp18 = tmp16 + tmp17;
	       tmp26 = tmp16 - tmp17;
	       tmp19 = c_re(input[2 * istride]);
	       tmp20 = c_re(input[7 * istride]);
	       tmp21 = tmp19 + tmp20;
	       tmp25 = tmp19 - tmp20;
	  }
	  tmp22 = tmp18 + tmp21;
	  tmp115 = tmp26 + tmp25;
	  {
	       fftw_real tmp2;
	       fftw_real tmp3;
	       fftw_real tmp4;
	       fftw_real tmp5;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp2 = c_re(input[istride]);
	       tmp3 = c_re(input[3 * istride]);
	       tmp4 = c_re(input[9 * istride]);
	       tmp5 = tmp3 + tmp4;
	       tmp6 = tmp2 + tmp5;
	       tmp32 = tmp2 - (K500000000 * tmp5);
	       tmp28 = tmp3 - tmp4;
	  }
	  {
	       fftw_real tmp7;
	       fftw_real tmp8;
	       fftw_real tmp9;
	       fftw_real tmp10;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp7 = c_re(input[12 * istride]);
	       tmp8 = c_re(input[4 * istride]);
	       tmp9 = c_re(input[10 * istride]);
	       tmp10 = tmp8 + tmp9;
	       tmp11 = tmp7 + tmp10;
	       tmp33 = tmp7 - (K500000000 * tmp10);
	       tmp29 = tmp8 - tmp9;
	  }
	  tmp113 = tmp6 - tmp11;
	  {
	       fftw_real tmp12;
	       fftw_real tmp23;
	       fftw_real tmp34;
	       fftw_real tmp35;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp12 = tmp6 + tmp11;
	       tmp23 = tmp15 + tmp22;
	       tmp24 = tmp12 + tmp23;
	       tmp38 = K300462606 * (tmp12 - tmp23);
	       tmp34 = tmp32 + tmp33;
	       tmp35 = tmp15 - (K500000000 * tmp22);
	       tmp36 = tmp34 - tmp35;
	       tmp41 = tmp34 + tmp35;
	  }
	  tmp116 = tmp114 - tmp115;
	  tmp118 = K866025403 * (tmp28 + tmp29);
	  tmp119 = tmp114 + (K500000000 * tmp115);
	  tmp120 = tmp118 + tmp119;
	  tmp125 = tmp119 - tmp118;
	  {
	       fftw_real tmp27;
	       fftw_real tmp30;
	       fftw_real tmp121;
	       fftw_real tmp122;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp27 = tmp25 - tmp26;
	       tmp30 = tmp28 - tmp29;
	       tmp31 = tmp27 - tmp30;
	       tmp40 = tmp30 + tmp27;
	       tmp121 = tmp32 - tmp33;
	       tmp122 = K866025403 * (tmp18 - tmp21);
	       tmp123 = tmp121 - tmp122;
	       tmp126 = tmp121 + tmp122;
	  }
     }
     {
	  fftw_real tmp48;
	  fftw_real tmp131;
	  fftw_real tmp66;
	  fftw_real tmp70;
	  fftw_real tmp77;
	  fftw_real tmp61;
	  fftw_real tmp69;
	  fftw_real tmp76;
	  fftw_real tmp51;
	  fftw_real tmp73;
	  fftw_real tmp54;
	  fftw_real tmp72;
	  fftw_real tmp55;
	  fftw_real tmp132;
	  fftw_real tmp46;
	  fftw_real tmp47;
	  fftw_real tmp139;
	  fftw_real tmp140;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp46 = c_im(input[8 * istride]);
	  tmp47 = c_im(input[5 * istride]);
	  tmp48 = tmp46 - tmp47;
	  tmp131 = tmp46 + tmp47;
	  {
	       fftw_real tmp62;
	       fftw_real tmp63;
	       fftw_real tmp64;
	       fftw_real tmp65;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp62 = c_im(input[12 * istride]);
	       tmp63 = c_im(input[4 * istride]);
	       tmp64 = c_im(input[10 * istride]);
	       tmp65 = tmp63 + tmp64;
	       tmp66 = tmp62 + tmp65;
	       tmp70 = tmp62 - (K500000000 * tmp65);
	       tmp77 = tmp63 - tmp64;
	  }
	  {
	       fftw_real tmp57;
	       fftw_real tmp58;
	       fftw_real tmp59;
	       fftw_real tmp60;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp57 = c_im(input[istride]);
	       tmp58 = c_im(input[3 * istride]);
	       tmp59 = c_im(input[9 * istride]);
	       tmp60 = tmp58 + tmp59;
	       tmp61 = tmp57 + tmp60;
	       tmp69 = tmp57 - (K500000000 * tmp60);
	       tmp76 = tmp58 - tmp59;
	  }
	  {
	       fftw_real tmp49;
	       fftw_real tmp50;
	       fftw_real tmp52;
	       fftw_real tmp53;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp49 = c_im(input[6 * istride]);
	       tmp50 = c_im(input[11 * istride]);
	       tmp51 = tmp49 - tmp50;
	       tmp73 = tmp49 + tmp50;
	       tmp52 = c_im(input[2 * istride]);
	       tmp53 = c_im(input[7 * istride]);
	       tmp54 = tmp52 - tmp53;
	       tmp72 = tmp52 + tmp53;
	  }
	  tmp55 = tmp51 + tmp54;
	  tmp132 = tmp73 + tmp72;
	  tmp56 = tmp48 - tmp55;
	  {
	       fftw_real tmp78;
	       fftw_real tmp79;
	       fftw_real tmp135;
	       fftw_real tmp136;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp78 = K866025403 * (tmp76 + tmp77);
	       tmp79 = tmp48 + (K500000000 * tmp55);
	       tmp80 = tmp78 - tmp79;
	       tmp82 = tmp78 + tmp79;
	       tmp135 = tmp51 - tmp54;
	       tmp136 = tmp77 - tmp76;
	       tmp137 = tmp135 - tmp136;
	       tmp144 = tmp136 + tmp135;
	  }
	  tmp67 = tmp61 - tmp66;
	  tmp139 = tmp61 + tmp66;
	  tmp140 = tmp131 + tmp132;
	  tmp141 = K300462606 * (tmp139 - tmp140);
	  tmp147 = tmp139 + tmp140;
	  {
	       fftw_real tmp130;
	       fftw_real tmp133;
	       fftw_real tmp71;
	       fftw_real tmp74;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp130 = tmp69 + tmp70;
	       tmp133 = tmp131 - (K500000000 * tmp132);
	       tmp134 = tmp130 - tmp133;
	       tmp143 = tmp130 + tmp133;
	       tmp71 = tmp69 - tmp70;
	       tmp74 = K866025403 * (tmp72 - tmp73);
	       tmp75 = tmp71 - tmp74;
	       tmp83 = tmp71 + tmp74;
	  }
     }
     c_re(output[0]) = tmp1 + tmp24;
     {
	  fftw_real tmp100;
	  fftw_real tmp108;
	  fftw_real tmp39;
	  fftw_real tmp105;
	  fftw_real tmp95;
	  fftw_real tmp44;
	  fftw_real tmp68;
	  fftw_real tmp85;
	  fftw_real tmp96;
	  fftw_real tmp106;
	  fftw_real tmp88;
	  fftw_real tmp91;
	  fftw_real tmp101;
	  fftw_real tmp109;
	  fftw_real tmp98;
	  fftw_real tmp99;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp98 = (K387390585 * tmp31) - (K265966249 * tmp36);
	  tmp99 = (K113854479 * tmp40) - (K503537032 * tmp41);
	  tmp100 = tmp98 + tmp99;
	  tmp108 = tmp99 - tmp98;
	  {
	       fftw_real tmp37;
	       fftw_real tmp94;
	       fftw_real tmp42;
	       fftw_real tmp43;
	       fftw_real tmp93;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp37 = (K132983124 * tmp31) + (K258260390 * tmp36);
	       tmp94 = tmp38 - tmp37;
	       tmp42 = (K251768516 * tmp40) + (K075902986 * tmp41);
	       tmp43 = tmp1 - (K083333333 * tmp24);
	       tmp93 = tmp43 - tmp42;
	       tmp39 = (K2_000000000 * tmp37) + tmp38;
	       tmp105 = tmp94 + tmp93;
	       tmp95 = tmp93 - tmp94;
	       tmp44 = (K2_000000000 * tmp42) + tmp43;
	  }
	  {
	       fftw_real tmp81;
	       fftw_real tmp84;
	       fftw_real tmp89;
	       fftw_real tmp90;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp68 = (K575140729 * tmp56) - (K174138601 * tmp67);
	       tmp81 = (K011599105 * tmp75) - (K300238635 * tmp80);
	       tmp84 = (K256247671 * tmp82) + (K156891391 * tmp83);
	       tmp85 = tmp81 - tmp84;
	       tmp96 = K1_732050807 * (tmp81 + tmp84);
	       tmp106 = tmp68 - tmp85;
	       tmp88 = (K575140729 * tmp67) + (K174138601 * tmp56);
	       tmp89 = (K256247671 * tmp83) - (K156891391 * tmp82);
	       tmp90 = (K011599105 * tmp80) + (K300238635 * tmp75);
	       tmp91 = tmp89 - tmp90;
	       tmp101 = tmp88 + tmp91;
	       tmp109 = K1_732050807 * (tmp90 + tmp89);
	  }
	  {
	       fftw_real tmp45;
	       fftw_real tmp86;
	       fftw_real tmp103;
	       fftw_real tmp104;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp45 = tmp39 + tmp44;
	       tmp86 = tmp68 + (K2_000000000 * tmp85);
	       c_re(output[12 * ostride]) = tmp45 - tmp86;
	       c_re(output[ostride]) = tmp45 + tmp86;
	       {
		    fftw_real tmp87;
		    fftw_real tmp92;
		    fftw_real tmp97;
		    fftw_real tmp102;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp87 = tmp44 - tmp39;
		    tmp92 = tmp88 - (K2_000000000 * tmp91);
		    c_re(output[5 * ostride]) = tmp87 - tmp92;
		    c_re(output[8 * ostride]) = tmp87 + tmp92;
		    tmp97 = tmp95 - tmp96;
		    tmp102 = tmp100 + tmp101;
		    c_re(output[2 * ostride]) = tmp97 - tmp102;
		    c_re(output[7 * ostride]) = tmp97 + tmp102;
	       }
	       tmp103 = tmp95 + tmp96;
	       tmp104 = tmp101 - tmp100;
	       c_re(output[6 * ostride]) = tmp103 - tmp104;
	       c_re(output[11 * ostride]) = tmp103 + tmp104;
	       {
		    fftw_real tmp111;
		    fftw_real tmp112;
		    fftw_real tmp107;
		    fftw_real tmp110;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp111 = tmp105 - tmp106;
		    tmp112 = tmp109 - tmp108;
		    c_re(output[4 * ostride]) = tmp111 - tmp112;
		    c_re(output[10 * ostride]) = tmp111 + tmp112;
		    tmp107 = tmp105 + tmp106;
		    tmp110 = tmp108 + tmp109;
		    c_re(output[3 * ostride]) = tmp107 - tmp110;
		    c_re(output[9 * ostride]) = tmp107 + tmp110;
	       }
	  }
     }
     c_im(output[0]) = tmp147 + tmp146;
     {
	  fftw_real tmp160;
	  fftw_real tmp173;
	  fftw_real tmp142;
	  fftw_real tmp170;
	  fftw_real tmp165;
	  fftw_real tmp149;
	  fftw_real tmp117;
	  fftw_real tmp128;
	  fftw_real tmp162;
	  fftw_real tmp169;
	  fftw_real tmp151;
	  fftw_real tmp154;
	  fftw_real tmp157;
	  fftw_real tmp172;
	  fftw_real tmp158;
	  fftw_real tmp159;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp158 = (K387390585 * tmp137) + (K265966249 * tmp134);
	  tmp159 = (K113854479 * tmp144) + (K503537032 * tmp143);
	  tmp160 = tmp158 + tmp159;
	  tmp173 = tmp158 - tmp159;
	  {
	       fftw_real tmp138;
	       fftw_real tmp164;
	       fftw_real tmp145;
	       fftw_real tmp148;
	       fftw_real tmp163;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp138 = (K258260390 * tmp134) - (K132983124 * tmp137);
	       tmp164 = tmp141 - tmp138;
	       tmp145 = (K075902986 * tmp143) - (K251768516 * tmp144);
	       tmp148 = tmp146 - (K083333333 * tmp147);
	       tmp163 = tmp148 - tmp145;
	       tmp142 = (K2_000000000 * tmp138) + tmp141;
	       tmp170 = tmp164 + tmp163;
	       tmp165 = tmp163 - tmp164;
	       tmp149 = (K2_000000000 * tmp145) + tmp148;
	  }
	  {
	       fftw_real tmp124;
	       fftw_real tmp127;
	       fftw_real tmp152;
	       fftw_real tmp153;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp117 = (K174138601 * tmp113) - (K575140729 * tmp116);
	       tmp124 = (K256247671 * tmp120) + (K156891391 * tmp123);
	       tmp127 = (K300238635 * tmp125) + (K011599105 * tmp126);
	       tmp128 = tmp124 - tmp127;
	       tmp162 = K1_732050807 * (tmp124 + tmp127);
	       tmp169 = tmp117 - tmp128;
	       tmp151 = (K575140729 * tmp113) + (K174138601 * tmp116);
	       tmp152 = (K256247671 * tmp123) - (K156891391 * tmp120);
	       tmp153 = (K011599105 * tmp125) - (K300238635 * tmp126);
	       tmp154 = tmp152 + tmp153;
	       tmp157 = tmp151 + tmp154;
	       tmp172 = K1_732050807 * (tmp153 - tmp152);
	  }
	  {
	       fftw_real tmp129;
	       fftw_real tmp150;
	       fftw_real tmp167;
	       fftw_real tmp168;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp129 = tmp117 + (K2_000000000 * tmp128);
	       tmp150 = tmp142 + tmp149;
	       c_im(output[ostride]) = tmp129 + tmp150;
	       c_im(output[12 * ostride]) = tmp150 - tmp129;
	       {
		    fftw_real tmp155;
		    fftw_real tmp156;
		    fftw_real tmp161;
		    fftw_real tmp166;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp155 = tmp151 - (K2_000000000 * tmp154);
		    tmp156 = tmp149 - tmp142;
		    c_im(output[5 * ostride]) = tmp155 + tmp156;
		    c_im(output[8 * ostride]) = tmp156 - tmp155;
		    tmp161 = tmp157 + tmp160;
		    tmp166 = tmp162 + tmp165;
		    c_im(output[2 * ostride]) = tmp161 + tmp166;
		    c_im(output[7 * ostride]) = tmp166 - tmp161;
	       }
	       tmp167 = tmp165 - tmp162;
	       tmp168 = tmp160 - tmp157;
	       c_im(output[6 * ostride]) = tmp167 - tmp168;
	       c_im(output[11 * ostride]) = tmp168 + tmp167;
	       {
		    fftw_real tmp175;
		    fftw_real tmp176;
		    fftw_real tmp171;
		    fftw_real tmp174;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp175 = tmp170 - tmp169;
		    tmp176 = tmp172 - tmp173;
		    c_im(output[4 * ostride]) = tmp175 - tmp176;
		    c_im(output[10 * ostride]) = tmp176 + tmp175;
		    tmp171 = tmp169 + tmp170;
		    tmp174 = tmp172 + tmp173;
		    c_im(output[3 * ostride]) = tmp171 - tmp174;
		    c_im(output[9 * ostride]) = tmp174 + tmp171;
	       }
	  }
     }
}

fftw_codelet_desc fftwi_no_twiddle_13_desc = {
     "fftwi_no_twiddle_13",
     (void (*)()) fftwi_no_twiddle_13,
     13,
     FFTW_BACKWARD,
     FFTW_NOTW,
     298,
     0,
     (const int *) 0,
};
