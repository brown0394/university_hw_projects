module IsDefused(in,out);

input [7:0] in;
output out;

wire [7:0] b0;
wire  w9;
wire  b0_0_w1;
wire  b0_1_w2;
wire  b0_2_w3;
wire  b0_3_w4;
wire  b0_4_w5;
wire  b0_5_w6;
wire  b0_6_w7;
wire  b0_7_w8;

assign b0 = in;
assign out = w9;

assign b0_0_w1 = {b0[0]};
assign b0_1_w2 = {b0[1]};
assign b0_2_w3 = {b0[2]};
assign b0_3_w4 = {b0[3]};
assign b0_4_w5 = {b0[4]};
assign b0_5_w6 = {b0[5]};
assign b0_6_w7 = {b0[6]};
assign b0_7_w8 = {b0[7]};

PNU_AND8
     s0 (
      .i8(b0_0_w1),
      .i7(b0_1_w2),
      .i6(b0_2_w3),
      .i5(b0_3_w4),
      .i4(b0_4_w5),
      .i3(b0_5_w6),
      .i2(b0_6_w7),
      .i1(b0_7_w8),
      .o1(w9));

endmodule

