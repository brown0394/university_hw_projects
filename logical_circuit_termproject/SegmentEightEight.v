module SegmentEightEight(IN,Out,bomb);

input [7:0] IN;
output [7:0] Out;
input bomb;

wire [7:0] b2;
wire [7:0] b4;
wire  w27;
wire  b4_7_w3;
wire  b4_6_w6;
wire  b4_5_w7;
wire  b4_4_w9;
wire  b4_3_w11;
wire  b4_2_w13;
wire  b4_0_w16;
wire  b2_0;
wire  b2_1;
wire  b2_2;
wire  b2_3;
wire  b2_4;
wire  b2_5;
wire  b2_6;
wire  b2_7;
wire  b4_1_w26;

assign b4 = IN;
assign Out = b2;
assign w27 = bomb;

assign b2[7] = b2_7;
assign b2[6] = b2_6;
assign b2[5] = b2_5;
assign b2[4] = b2_4;
assign b2[3] = b2_3;
assign b2[2] = b2_2;
assign b2[1] = b2_1;
assign b2[0] = b2_0;

assign b4_7_w3 = {b4[7]};
assign b4_6_w6 = {b4[6]};
assign b4_5_w7 = {b4[5]};
assign b4_4_w9 = {b4[4]};
assign b4_3_w11 = {b4[3]};
assign b4_2_w13 = {b4[2]};
assign b4_0_w16 = {b4[0]};
assign b4_1_w26 = {b4[1]};

PNU_OR2
     s16 (
      .i1(b4_7_w3),
      .o1(b2_7),
      .i2(w27));

PNU_OR2
     s17 (
      .i2(b4_6_w6),
      .o1(b2_6),
      .i1(w27));

PNU_OR2
     s18 (
      .i1(b4_5_w7),
      .o1(b2_5),
      .i2(w27));

PNU_OR2
     s19 (
      .i1(b4_4_w9),
      .o1(b2_4),
      .i2(w27));

PNU_OR2
     s20 (
      .i1(b4_3_w11),
      .o1(b2_3),
      .i2(w27));

PNU_OR2
     s21 (
      .i1(b4_2_w13),
      .o1(b2_2),
      .i2(w27));

PNU_OR2
     s23 (
      .i1(b4_0_w16),
      .o1(b2_0),
      .i2(w27));

PNU_OR2
     s22 (
      .o1(b2_1),
      .i1(b4_1_w26),
      .i2(w27));

endmodule

