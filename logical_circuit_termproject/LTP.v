module LTP(Level,clk,rst,Pulse);

input Level;
input clk;
input rst;
output Pulse;

wire  w0;
wire  w1;
wire  w3;
wire  w4;
wire  w6;
wire  w7;
wire  w8;
wire  w9;

assign w9 = Level;
assign w1 = clk;
assign w0 = rst;
assign Pulse = w6;

PNU_DFF
     s0 (
      .reset(w0),
      .clock(w1),
      .Q(w8),
      .D(w9));

PNU_DFF
     s1 (
      .reset(w0),
      .clock(w1),
      .Q(w3),
      .D(w7));

PNU_AND2
     s3 (
      .i2(w4),
      .o1(w6),
      .i1(w8));

PNU_NOT
     s4 (
      .i1(w3),
      .o1(w4));

PNU_AND2
     s2 (
      .o1(w7),
      .i2(w8),
      .i1(w9));

endmodule

