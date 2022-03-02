module Enablechk(Input,out);

input [7:0] Input;
output out;

wire [7:0] b9;
wire  w17;
wire  b9_7_w9;
wire  b9_6_w10;
wire  b9_5_w11;
wire  b9_4_w13;
wire  b9_3_w12;
wire  b9_2_w14;
wire  b9_1_w15;
wire  b9_0_w16;

assign b9 = Input;
assign out = w17;

assign b9_7_w9 = {b9[7]};
assign b9_6_w10 = {b9[6]};
assign b9_5_w11 = {b9[5]};
assign b9_4_w13 = {b9[4]};
assign b9_3_w12 = {b9[3]};
assign b9_2_w14 = {b9[2]};
assign b9_1_w15 = {b9[1]};
assign b9_0_w16 = {b9[0]};

PNU_OR8
     s2 (
      .i8(b9_7_w9),
      .i7(b9_6_w10),
      .i6(b9_5_w11),
      .i5(b9_4_w13),
      .i4(b9_3_w12),
      .i3(b9_2_w14),
      .i2(b9_1_w15),
      .i1(b9_0_w16),
      .o1(w17));

endmodule

