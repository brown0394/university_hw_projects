module isisfirst(clk,rst,out);

input clk;
input rst;
output out;

wire  w9;
wire  w10;
wire  w12;
wire  w15;
wire  w16;
wire  w11;
wire  w13;
wire  w18;
wire  w14;
wire  w17;
wire  w19;
wire  w20;

assign w9 = clk;
assign w10 = rst;
assign out = w12;

PNU_DFF
     s0 (
      .clock(w9),
      .reset(w10),
      .D(w11),
      .Q(w17));

PNU_DFF
     s1 (
      .clock(w9),
      .reset(w10),
      .Q(w15),
      .D(w14));

PNU_NOT
     s3 (
      .i1(w15),
      .o1(w13));

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
      .i1(w17));

PNU_NOT
     s7 (
      .o1(w18),
      .i1(w17));

PNU_AND2
     s8 (
      .i2(w15),
      .i1(w16),
      .o1(w11));

PNU_AND2
     s9 (
      .i2(w13),
      .i1(w18),
      .o1(w14));

PNU_NOT
     s10 (
      .i1(w15),
      .o1(w20));

PNU_AND2
     s11 (
      .i1(w17),
      .o1(w19),
      .i2(w20));

endmodule

