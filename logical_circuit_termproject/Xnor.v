module Xnor(IN,SV,Out,en);

input [7:0] IN;
input [7:0] SV;
output [7:0] Out;
input en;

wire [7:0] b2;
wire [7:0] b3;
wire [7:0] b4;
wire  w21;
wire  w22;
wire  w25;
wire  w26;
wire  w28;
wire  w30;
wire  w32;
wire  w34;
wire  w29;
wire  w35;
wire  w38;
wire  w39;
wire  w42;
wire  w45;
wire  w47;
wire  w49;
wire  w43;
wire  b4_7_w3;
wire  b3_7_w4;
wire  b3_6_w5;
wire  b4_6_w6;
wire  b4_5_w7;
wire  b3_5_w8;
wire  b4_4_w9;
wire  b3_4_w10;
wire  b4_3_w11;
wire  b3_3_w12;
wire  b4_2_w13;
wire  b4_1_w15;
wire  b4_0_w16;
wire  b3_0_w17;
wire  b3_1_w18;
wire  b3_2_w19;
wire  b2_7;
wire  b2_6;
wire  b2_5;
wire  b2_4;
wire  b2_3;
wire  b2_2;
wire  b2_1;
wire  b2_0;

assign b4 = IN;
assign b3 = SV;
assign Out = b2;
assign w43 = en;

assign b2[7] = b2_7;
assign b2[6] = b2_6;
assign b2[5] = b2_5;
assign b2[4] = b2_4;
assign b2[3] = b2_3;
assign b2[2] = b2_2;
assign b2[1] = b2_1;
assign b2[0] = b2_0;

assign b4_7_w3 = {b4[7]};
assign b3_7_w4 = {b3[7]};
assign b3_6_w5 = {b3[6]};
assign b4_6_w6 = {b4[6]};
assign b4_5_w7 = {b4[5]};
assign b3_5_w8 = {b3[5]};
assign b4_4_w9 = {b4[4]};
assign b3_4_w10 = {b3[4]};
assign b4_3_w11 = {b4[3]};
assign b3_3_w12 = {b3[3]};
assign b4_2_w13 = {b4[2]};
assign b4_1_w15 = {b4[1]};
assign b4_0_w16 = {b4[0]};
assign b3_0_w17 = {b3[0]};
assign b3_1_w18 = {b3[1]};
assign b3_2_w19 = {b3[2]};

PNU_XOR2
     s0 (
      .i1(b4_7_w3),
      .i2(b3_7_w4),
      .o1(w21));

PNU_XOR2
     s1 (
      .i1(b3_6_w5),
      .i2(b4_6_w6),
      .o1(w22));

PNU_XOR2
     s2 (
      .i1(b4_5_w7),
      .i2(b3_5_w8),
      .o1(w25));

PNU_XOR2
     s3 (
      .i1(b4_4_w9),
      .i2(b3_4_w10),
      .o1(w26));

PNU_XOR2
     s4 (
      .i1(b4_3_w11),
      .i2(b3_3_w12),
      .o1(w28));

PNU_XOR2
     s5 (
      .i1(b4_2_w13),
      .i2(b3_2_w19),
      .o1(w30));

PNU_XOR2
     s6 (
      .i1(b4_1_w15),
      .i2(b3_1_w18),
      .o1(w32));

PNU_XOR2
     s7 (
      .i1(b4_0_w16),
      .i2(b3_0_w17),
      .o1(w34));

PNU_NOT
     s8 (
      .i1(w21),
      .o1(w29));

PNU_NOT
     s9 (
      .i1(w22),
      .o1(w35));

PNU_NOT
     s10 (
      .i1(w25),
      .o1(w38));

PNU_NOT
     s11 (
      .i1(w26),
      .o1(w39));

PNU_NOT
     s12 (
      .i1(w28),
      .o1(w42));

PNU_NOT
     s13 (
      .i1(w30),
      .o1(w45));

PNU_NOT
     s14 (
      .i1(w32),
      .o1(w47));

PNU_NOT
     s15 (
      .i1(w34),
      .o1(w49));

PNU_AND2
     s16 (
      .i1(w29),
      .o1(b2_7),
      .i2(w43));

PNU_AND2
     s17 (
      .o1(b2_6),
      .i1(w35),
      .i2(w43));

PNU_AND2
     s18 (
      .o1(b2_5),
      .i1(w38),
      .i2(w43));

PNU_AND2
     s19 (
      .i1(w39),
      .o1(b2_4),
      .i2(w43));

PNU_AND2
     s20 (
      .o1(b2_3),
      .i1(w42),
      .i2(w43));

PNU_AND2
     s21 (
      .o1(b2_2),
      .i1(w45),
      .i2(w43));

PNU_AND2
     s22 (
      .o1(b2_1),
      .i1(w47),
      .i2(w43));

PNU_AND2
     s23 (
      .o1(b2_0),
      .i1(w49),
      .i2(w43));

endmodule

