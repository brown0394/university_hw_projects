module DifModSelector(Mod1,Mod2,Out,difMod);

input [7:0] Mod1;
input [7:0] Mod2;
output [7:0] Out;
input difMod;

wire [7:0] b2;
wire [7:0] b3;
wire [7:0] b4;
wire  w42;
wire  w30;
wire  w44;
wire  w45;
wire  w46;
wire  w47;
wire  w48;
wire  w49;
wire  w50;
wire  w51;
wire  w52;
wire  w53;
wire  w54;
wire  w55;
wire  w56;
wire  w57;
wire  w58;
wire  w59;
wire  b2_0;
wire  b2_1;
wire  b2_2;
wire  b2_3;
wire  b2_4;
wire  b2_5;
wire  b2_6;
wire  b2_7;
wire  b4_7_w13;
wire  b3_7_w15;
wire  b4_6_w17;
wire  b3_6_w18;
wire  b4_5_w20;
wire  b3_5_w21;
wire  b4_4_w23;
wire  b3_4_w24;
wire  b4_3_w25;
wire  b3_3_w27;
wire  b4_2_w28;
wire  b3_2_w29;
wire  b4_1_w39;
wire  b3_1_w40;
wire  b4_0_w41;
wire  b3_0_w43;

assign b4 = Mod1;
assign b3 = Mod2;
assign Out = b2;
assign w30 = difMod;

assign b2[7] = b2_7;
assign b2[6] = b2_6;
assign b2[5] = b2_5;
assign b2[4] = b2_4;
assign b2[3] = b2_3;
assign b2[2] = b2_2;
assign b2[1] = b2_1;
assign b2[0] = b2_0;

assign b4_7_w13 = {b4[7]};
assign b3_7_w15 = {b3[7]};
assign b4_6_w17 = {b4[6]};
assign b3_6_w18 = {b3[6]};
assign b4_5_w20 = {b4[5]};
assign b3_5_w21 = {b3[5]};
assign b4_4_w23 = {b4[4]};
assign b3_4_w24 = {b3[4]};
assign b4_3_w25 = {b4[3]};
assign b3_3_w27 = {b3[3]};
assign b4_2_w28 = {b4[2]};
assign b3_2_w29 = {b3[2]};
assign b4_1_w39 = {b4[1]};
assign b3_1_w40 = {b3[1]};
assign b4_0_w41 = {b4[0]};
assign b3_0_w43 = {b3[0]};

PNU_OR2
     s16 (
      .o1(b2_7),
      .i1(w44),
      .i2(w45));

PNU_OR2
     s17 (
      .o1(b2_6),
      .i1(w46),
      .i2(w47));

PNU_OR2
     s18 (
      .o1(b2_5),
      .i1(w48),
      .i2(w49));

PNU_OR2
     s19 (
      .o1(b2_4),
      .i1(w50),
      .i2(w51));

PNU_OR2
     s20 (
      .o1(b2_3),
      .i1(w52),
      .i2(w53));

PNU_OR2
     s21 (
      .o1(b2_2),
      .i1(w54),
      .i2(w55));

PNU_OR2
     s22 (
      .o1(b2_1),
      .i1(w56),
      .i2(w57));

PNU_OR2
     s23 (
      .o1(b2_0),
      .i1(w58),
      .i2(w59));

PNU_NOT
     s8 (
      .o1(w42),
      .i1(w30));

PNU_AND2
     s9 (
      .i1(b4_7_w13),
      .i2(w42),
      .o1(w44));

PNU_AND2
     s10 (
      .i1(b3_7_w15),
      .i2(w30),
      .o1(w45));

PNU_AND2
     s11 (
      .i1(b4_6_w17),
      .i2(w42),
      .o1(w46));

PNU_AND2
     s12 (
      .i1(b3_6_w18),
      .i2(w30),
      .o1(w47));

PNU_AND2
     s13 (
      .i1(b4_5_w20),
      .i2(w42),
      .o1(w48));

PNU_AND2
     s14 (
      .i1(b3_5_w21),
      .i2(w30),
      .o1(w49));

PNU_AND2
     s15 (
      .i1(b4_4_w23),
      .i2(w42),
      .o1(w50));

PNU_AND2
     s24 (
      .i1(b3_4_w24),
      .i2(w30),
      .o1(w51));

PNU_AND2
     s25 (
      .i1(b4_3_w25),
      .i2(w42),
      .o1(w52));

PNU_AND2
     s26 (
      .i1(b3_3_w27),
      .i2(w30),
      .o1(w53));

PNU_AND2
     s27 (
      .i1(b4_2_w28),
      .i2(w42),
      .o1(w54));

PNU_AND2
     s28 (
      .i1(b3_2_w29),
      .i2(w30),
      .o1(w55));

PNU_AND2
     s29 (
      .i1(b4_1_w39),
      .i2(w42),
      .o1(w56));

PNU_AND2
     s30 (
      .i1(b3_1_w40),
      .i2(w30),
      .o1(w57));

PNU_AND2
     s31 (
      .i1(b4_0_w41),
      .i2(w42),
      .o1(w58));

PNU_AND2
     s32 (
      .i1(b3_0_w43),
      .i2(w30),
      .o1(w59));

endmodule

