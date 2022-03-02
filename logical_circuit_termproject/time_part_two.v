module time_part_two(minten,timemod,rst,hepta,heptazero,trizero);

input minten;
input timemod;
input rst;
output [2:0] hepta;
output heptazero;
output trizero;

wire [2:0] b0;
wire [1:0] b1;
wire  w3;
wire  w4;
wire  w11;
wire  w14;
wire  w15;
wire  w16;
wire  w17;
wire  w18;
wire  w25;
wire  w26;
wire  w27;
wire [2:0] b19;
wire  w24;
wire  w28;
wire  b0_0_w20;
wire  b0_1_w21;
wire  b0_2_w22;
wire  b1_0_w19;
wire  b1_1_w23;

assign w3 = minten;
assign w24 = timemod;
assign w4 = rst;
assign hepta = b19;
assign heptazero = w27;
assign trizero = w28;

assign b0_0_w20 = {b0[0]};
assign b0_1_w21 = {b0[1]};
assign b0_2_w22 = {b0[2]};
assign b1_0_w19 = {b1[0]};
assign b1_1_w23 = {b1[1]};

Hepta_counter
     s3 (
      .cnt10(b0),
      .clk(w3),
      .rst(w4));

TriMode
     s29 (
      .cnt3(b1),
      .clk(w3),
      .rst(w4));

timeModeSelect
     s31 (
      .hept(b0),
      .tripl(b1),
      .out(b19),
      .mod(w24));

PNU_NOT
     s4 (
      .o1(w11),
      .i1(b0_2_w22));

PNU_NOT
     s6 (
      .o1(w14),
      .i1(b0_1_w21));

PNU_NOT
     s7 (
      .o1(w15),
      .i1(b0_0_w20));

PNU_AND3
     s8 (
      .i1(w11),
      .i2(w14),
      .i3(w15),
      .o1(w25));

PNU_NOT
     s9 (
      .o1(w17),
      .i1(b1_0_w19));

PNU_NOT
     s10 (
      .o1(w18),
      .i1(b1_1_w23));

PNU_AND2
     s11 (
      .o1(w16),
      .i1(w17),
      .i2(w18));

PNU_NOT
     s12 (
      .o1(w26),
      .i1(w24));

PNU_AND2
     s13 (
      .i1(w25),
      .i2(w26),
      .o1(w27));

PNU_AND2
     s14 (
      .i2(w16),
      .i1(w24),
      .o1(w28));

endmodule

