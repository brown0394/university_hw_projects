module TriMode(clk,rst,cnt3);

input clk;
input rst;
output [1:0] cnt3;

wire  w23;
wire  w24;
wire  w9;
wire [1:0] b10;
wire  w16;
wire  w18;
wire  w10;
wire  w11;
wire  b10_0;
wire  b10_0_w12;
wire  b10_1;
wire  b10_1_w13;

assign w24 = clk;
assign w23 = rst;
assign cnt3 = b10;

assign b10[1] = b10_1;
assign b10[0] = b10_0;

assign b10_0_w12 = {b10[0]};
assign b10_1_w13 = {b10[1]};

PNU_NOT
     s3 (
      .o1(w9),
      .i1(b10_1_w13));

PNU_AND2
     s4 (
      .i1(w9),
      .i2(w16),
      .o1(w10));

PNU_AND2
     s5 (
      .i2(w18),
      .i1(b10_1_w13),
      .o1(w11));

PNU_NOT
     s6 (
      .o1(w16),
      .i1(b10_0_w12));

PNU_NOT
     s7 (
      .o1(w18),
      .i1(b10_0_w12));

PNU_DFF
     s8 (
      .reset(w23),
      .clock(w24),
      .Q(b10_1),
      .D(w10));

PNU_DFF
     s9 (
      .reset(w23),
      .clock(w24),
      .Q(b10_0),
      .D(w11));

endmodule

