module TwoFourEight(orr,xorr,norr,xnorr,out);

input [7:0] orr;
input [7:0] xorr;
input [7:0] norr;
input [7:0] xnorr;
output [7:0] out;

wire [7:0] b1;
wire [7:0] b2;
wire [7:0] b3;
wire [7:0] b4;
wire [7:0] b44;
wire  b1_7_w4;
wire  b2_7_w5;
wire  b3_7_w6;
wire  b4_7_w7;
wire  b1_6_w44;
wire  b2_6_w45;
wire  b3_6_w46;
wire  b4_6_w47;
wire  b1_5_w48;
wire  b2_5_w49;
wire  b3_5_w50;
wire  b4_5_w51;
wire  b1_4_w52;
wire  b2_4_w53;
wire  b3_4_w54;
wire  b4_4_w55;
wire  b1_3_w56;
wire  b2_3_w57;
wire  b3_3_w58;
wire  b4_3_w59;
wire  b1_2_w60;
wire  b2_2_w61;
wire  b3_2_w62;
wire  b4_2_w63;
wire  b1_1_w64;
wire  b2_1_w65;
wire  b3_1_w66;
wire  b4_1_w67;
wire  b1_0_w68;
wire  b2_0_w69;
wire  b3_0_w70;
wire  b4_0_w71;
wire  b44_7;
wire  b44_6;
wire  b44_5;
wire  b44_4;
wire  b44_3;
wire  b44_2;
wire  b44_1;
wire  b44_0;

assign b1 = orr;
assign b2 = xorr;
assign b3 = norr;
assign b4 = xnorr;
assign out = b44;

assign b44[7] = b44_7;
assign b44[6] = b44_6;
assign b44[5] = b44_5;
assign b44[4] = b44_4;
assign b44[3] = b44_3;
assign b44[2] = b44_2;
assign b44[1] = b44_1;
assign b44[0] = b44_0;

assign b1_7_w4 = {b1[7]};
assign b2_7_w5 = {b2[7]};
assign b3_7_w6 = {b3[7]};
assign b4_7_w7 = {b4[7]};
assign b1_6_w44 = {b1[6]};
assign b2_6_w45 = {b2[6]};
assign b3_6_w46 = {b3[6]};
assign b4_6_w47 = {b4[6]};
assign b1_5_w48 = {b1[5]};
assign b2_5_w49 = {b2[5]};
assign b3_5_w50 = {b3[5]};
assign b4_5_w51 = {b4[5]};
assign b1_4_w52 = {b1[4]};
assign b2_4_w53 = {b2[4]};
assign b3_4_w54 = {b3[4]};
assign b4_4_w55 = {b4[4]};
assign b1_3_w56 = {b1[3]};
assign b2_3_w57 = {b2[3]};
assign b3_3_w58 = {b3[3]};
assign b4_3_w59 = {b4[3]};
assign b1_2_w60 = {b1[2]};
assign b2_2_w61 = {b2[2]};
assign b3_2_w62 = {b3[2]};
assign b4_2_w63 = {b4[2]};
assign b1_1_w64 = {b1[1]};
assign b2_1_w65 = {b2[1]};
assign b3_1_w66 = {b3[1]};
assign b4_1_w67 = {b4[1]};
assign b1_0_w68 = {b1[0]};
assign b2_0_w69 = {b2[0]};
assign b3_0_w70 = {b3[0]};
assign b4_0_w71 = {b4[0]};

PNU_OR4
     s0 (
      .i1(b1_7_w4),
      .i2(b2_7_w5),
      .i3(b3_7_w6),
      .i4(b4_7_w7),
      .o1(b44_7));

PNU_OR4
     s1 (
      .i1(b1_6_w44),
      .i2(b2_6_w45),
      .i3(b3_6_w46),
      .i4(b4_6_w47),
      .o1(b44_6));

PNU_OR4
     s2 (
      .i1(b1_5_w48),
      .i2(b2_5_w49),
      .i3(b3_5_w50),
      .i4(b4_5_w51),
      .o1(b44_5));

PNU_OR4
     s3 (
      .i1(b1_4_w52),
      .i2(b2_4_w53),
      .i3(b3_4_w54),
      .i4(b4_4_w55),
      .o1(b44_4));

PNU_OR4
     s4 (
      .i1(b1_3_w56),
      .i2(b2_3_w57),
      .i3(b3_3_w58),
      .i4(b4_3_w59),
      .o1(b44_3));

PNU_OR4
     s5 (
      .i1(b1_2_w60),
      .i2(b2_2_w61),
      .i3(b3_2_w62),
      .i4(b4_2_w63),
      .o1(b44_2));

PNU_OR4
     s6 (
      .i1(b1_1_w64),
      .i2(b2_1_w65),
      .i3(b3_1_w66),
      .i4(b4_1_w67),
      .o1(b44_1));

PNU_OR4
     s7 (
      .i1(b1_0_w68),
      .i2(b2_0_w69),
      .i3(b3_0_w70),
      .i4(b4_0_w71),
      .o1(b44_0));

endmodule

