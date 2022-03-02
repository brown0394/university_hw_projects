module register_8bit(Ce,clk,rst,Din,Dout);

input Ce;
input clk;
input rst;
input [7:0] Din;
output [7:0] Dout;

wire [7:0] b10;
wire  w20;
wire  w21;
wire  w19;
wire [7:0] b12;
wire  b10_0_w11;
wire  b10_1_w12;
wire  b10_2_w13;
wire  b10_3_w14;
wire  b10_4_w15;
wire  b10_5_w16;
wire  b10_6_w17;
wire  b10_7_w18;
wire  b12_7;
wire  b12_6;
wire  b12_5;
wire  b12_4;
wire  b12_3;
wire  b12_2;
wire  b12_1;
wire  b12_0;

assign w21 = Ce;
assign w20 = clk;
assign w19 = rst;
assign b10 = Din;
assign Dout = b12;

assign b12[7] = b12_7;
assign b12[6] = b12_6;
assign b12[5] = b12_5;
assign b12[4] = b12_4;
assign b12[3] = b12_3;
assign b12[2] = b12_2;
assign b12[1] = b12_1;
assign b12[0] = b12_0;

assign b10_0_w11 = {b10[0]};
assign b10_1_w12 = {b10[1]};
assign b10_2_w13 = {b10[2]};
assign b10_3_w14 = {b10[3]};
assign b10_4_w15 = {b10[4]};
assign b10_5_w16 = {b10[5]};
assign b10_6_w17 = {b10[6]};
assign b10_7_w18 = {b10[7]};

PNU_DFF_Ce
     s0 (
      .D(b10_0_w11),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_0));

PNU_DFF_Ce
     s1 (
      .D(b10_1_w12),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_1));

PNU_DFF_Ce
     s2 (
      .D(b10_2_w13),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_2));

PNU_DFF_Ce
     s3 (
      .D(b10_3_w14),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_3));

PNU_DFF_Ce
     s4 (
      .D(b10_4_w15),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_4));

PNU_DFF_Ce
     s5 (
      .D(b10_5_w16),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_5));

PNU_DFF_Ce
     s6 (
      .D(b10_6_w17),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_6));

PNU_DFF_Ce
     s7 (
      .D(b10_7_w18),
      .clock(w20),
      .Ce(w21),
      .reset(w19),
      .Q(b12_7));

endmodule

