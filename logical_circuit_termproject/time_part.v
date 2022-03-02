module time_part(clk,rst,minten,zero,LSB,seclock,decimal);

input clk;
input rst;
output minten;
output zero;
output LSB;
output seclock;
output [3:0] decimal;

wire  w1;
wire  w2;
wire  w6;
wire [3:0] b10;
wire  w13;
wire  w14;
wire  w12;
wire  w15;
wire  w16;
wire  w17;
wire  b10_2_w11;
wire  b10_1_w8;
wire  b10_0_w18;
wire  b10_3_w19;

assign w1 = clk;
assign w2 = rst;
assign minten = w6;
assign zero = w13;
assign LSB = b10[0];
assign seclock = w14;
assign decimal = b10;

assign b10_2_w11 = {b10[2]};
assign b10_1_w8 = {b10[1]};
assign b10_0_w18 = {b10[0]};
assign b10_3_w19 = {b10[3]};

ClockDivTen
     s0 (
      .clk(w1),
      .rst(w2),
      .out(w14));

Deci_counter
     s1 (
      .rst(w2),
      .clk(w14),
      .cnt10(b10));

PNU_AND2
     s2 (
      .o1(w6),
      .i2(b10_0_w18),
      .i1(b10_3_w19));

PNU_NOT
     s4 (
      .o1(w12),
      .i1(b10_3_w19));

PNU_NOT
     s5 (
      .i1(b10_2_w11),
      .o1(w15));

PNU_NOT
     s6 (
      .i1(b10_1_w8),
      .o1(w16));

PNU_NOT
     s7 (
      .o1(w17),
      .i1(b10_0_w18));

PNU_AND4
     s8 (
      .o1(w13),
      .i1(w12),
      .i2(w15),
      .i3(w16),
      .i4(w17));

endmodule

