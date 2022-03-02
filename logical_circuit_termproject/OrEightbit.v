module OrEightbit(IN,SV,Out,en);

input [7:0] IN;
input [7:0] SV;
output [7:0] Out;
input en;

wire [7:0] b2;
wire [7:0] b3;
wire [7:0] b4;
wire  w27;
wire  w39;
wire  w40;
wire  w41;
wire  w42;
wire  w43;
wire  w44;
wire  w45;
wire  w46;
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
wire  b2_0;
wire  b2_1;
wire  b2_2;
wire  b2_3;
wire  b2_4;
wire  b2_5;
wire  b2_6;
wire  b2_7;

assign b4 = IN;
assign b3 = SV;
assign Out = b2;
assign w27 = en;

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

PNU_AND2
     s8 (
      .i2(w27),
      .o1(b2_7),
      .i1(w46));

PNU_AND2
     s9 (
      .i2(w27),
      .o1(b2_6),
      .i1(w45));

PNU_AND2
     s10 (
      .i2(w27),
      .o1(b2_5),
      .i1(w44));

PNU_AND2
     s11 (
      .i2(w27),
      .o1(b2_4),
      .i1(w43));

PNU_AND2
     s12 (
      .i2(w27),
      .o1(b2_3),
      .i1(w42));

PNU_AND2
     s13 (
      .i2(w27),
      .o1(b2_2),
      .i1(w41));

PNU_AND2
     s14 (
      .i2(w27),
      .o1(b2_1),
      .i1(w40));

PNU_AND2
     s15 (
      .i2(w27),
      .o1(b2_0),
      .i1(w39));

PNU_OR2
     s16 (
      .i1(b4_7_w3),
      .i2(b3_7_w4),
      .o1(w46));

PNU_OR2
     s17 (
      .i1(b3_6_w5),
      .i2(b4_6_w6),
      .o1(w45));

PNU_OR2
     s18 (
      .i1(b4_5_w7),
      .i2(b3_5_w8),
      .o1(w44));

PNU_OR2
     s19 (
      .i1(b4_4_w9),
      .i2(b3_4_w10),
      .o1(w43));

PNU_OR2
     s20 (
      .i1(b4_3_w11),
      .i2(b3_3_w12),
      .o1(w42));

PNU_OR2
     s21 (
      .i1(b4_2_w13),
      .i2(b3_2_w19),
      .o1(w41));

PNU_OR2
     s22 (
      .i1(b4_1_w15),
      .i2(b3_1_w18),
      .o1(w40));

PNU_OR2
     s23 (
      .i1(b4_0_w16),
      .i2(b3_0_w17),
      .o1(w39));

endmodule

