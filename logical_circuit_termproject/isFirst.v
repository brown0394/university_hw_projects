module isFirst(clk,rst,out);

input clk;
input rst;
output out;

wire  w9;
wire  w10;
wire  w12;
wire  w16;
wire  w11;
wire  w14;
wire  w19;
wire  w20;
wire  w21;
wire  w15;
wire  w13;

assign w9 = clk;
assign w10 = rst;
assign out = w12;

PNU_DFF
     s0 (
      .clock(w9),
      .reset(w10),
      .D(w11),
      .Q(w13));

PNU_DFF
     s1 (
      .clock(w9),
      .reset(w10),
      .D(w14),
      .Q(w15));

PNU_DFF_Ce
     s5 (
      .clock(w9),
      .reset(w10),
      .Q(w12),
      .D(w19),
      .Ce(w19));

PNU_NOT
     s6 (
      .o1(w16),
      .i1(w13));

PNU_NOT
     s7 (
      .o1(w21),
      .i1(w15));

PNU_AND2
     s8 (
      .i1(w16),
      .o1(w11),
      .i2(w21));

PNU_NOT
     s10 (
      .o1(w20),
      .i1(w15));

PNU_AND2
     s11 (
      .o1(w19),
      .i2(w20),
      .i1(w13));

PNU_ZERO
     s9 (
      .o1(w14));

endmodule

