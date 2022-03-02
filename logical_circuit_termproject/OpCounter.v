module OpCounter(Input,rst,out);

input Input;
input rst;
output [2:0] out;

wire  w29;
wire [2:0] b24;
wire  w10;
wire  w11;
wire  w15;
wire  w16;
wire  w18;
wire  w20;
wire  w22;
wire  w23;
wire  w28;
wire  w26;
wire  w25;
wire  w24;
wire  b24_1;
wire  b24_1_w19;
wire  b24_0;
wire  b24_0_w21;
wire  b24_2;
wire  b24_2_w17;

assign w29 = Input;
assign w28 = rst;
assign out = b24;

assign b24[2] = b24_2;
assign b24[1] = b24_1;
assign b24[0] = b24_0;

assign b24_1_w19 = {b24[1]};
assign b24_0_w21 = {b24[0]};
assign b24_2_w17 = {b24[2]};

PNU_AND2
     s3 (
      .o1(w16),
      .i1(b24_1_w19),
      .i2(b24_0_w21));

PNU_AND3
     s4 (
      .i2(w10),
      .i3(w11),
      .o1(w15),
      .i1(b24_2_w17));

PNU_OR2
     s5 (
      .i2(w15),
      .i1(w16),
      .o1(w24));

PNU_NOT
     s6 (
      .o1(w11),
      .i1(b24_0_w21));

PNU_NOT
     s7 (
      .o1(w10),
      .i1(b24_1_w19));

PNU_AND2
     s9 (
      .i1(b24_1_w19),
      .i2(w20),
      .o1(w22));

PNU_OR2
     s10 (
      .i2(w22),
      .i1(w23),
      .o1(w25));

PNU_NOT
     s11 (
      .o1(w20),
      .i1(b24_0_w21));

PNU_NOT
     s13 (
      .o1(w18),
      .i1(b24_1_w19));

PNU_NOT
     s15 (
      .i1(b24_0_w21),
      .o1(w26));

PNU_AND2
     s14 (
      .i1(w18),
      .i2(b24_0_w21),
      .o1(w23));

PNU_DFF
     s12 (
      .clock(w29),
      .Q(b24_2),
      .reset(w28),
      .D(w24));

PNU_DFF
     s16 (
      .clock(w29),
      .Q(b24_1),
      .reset(w28),
      .D(w25));

PNU_DFF
     s17 (
      .clock(w29),
      .Q(b24_0),
      .reset(w28),
      .D(w26));

endmodule

