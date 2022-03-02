module Clock_Divisior(clk,rst,out);

input clk;
input rst;
output out;

wire  w0;
wire  w5;
wire  w7;
wire  w8;
wire  w9;
wire  w10;
wire  w11;
wire  w12;
wire  w13;
wire  w14;
wire  w15;
wire  w16;

assign w0 = clk;
assign w16 = rst;
assign out = w15;

PNU_DFF
     s0 (
      .clock(w0),
      .Q(w5),
      .D(w7),
      .reset(w16));

PNU_NOT
     s1 (
      .i1(w5),
      .o1(w7));

PNU_DFF
     s2 (
      .clock(w7),
      .Q(w8),
      .D(w9),
      .reset(w16));

PNU_NOT
     s3 (
      .i1(w8),
      .o1(w9));

PNU_DFF
     s4 (
      .clock(w9),
      .Q(w10),
      .D(w11),
      .reset(w16));

PNU_NOT
     s5 (
      .i1(w10),
      .o1(w11));

PNU_DFF
     s6 (
      .clock(w11),
      .Q(w12),
      .D(w13),
      .reset(w16));

PNU_NOT
     s7 (
      .i1(w12),
      .o1(w13));

PNU_DFF
     s8 (
      .clock(w13),
      .Q(w14),
      .D(w15),
      .reset(w16));

PNU_NOT
     s9 (
      .i1(w14),
      .o1(w15));

endmodule

