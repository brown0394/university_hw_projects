module ClockDivFive(clk,rst,out);

input clk;
input rst;
output out;

wire  w1;
wire  w5;
wire  w6;
wire  w8;
wire  w9;
wire  w10;
wire  w11;
wire  w12;
wire  w13;
wire  w14;
wire  w16;
wire  w17;
wire  w15;

assign w1 = clk;
assign w16 = rst;
assign out = w15;

Clock_Divisior
     s0 (
      .clk(w1),
      .out(w6),
      .rst(w16));

Clock_Divisior
     s1 (
      .out(w5),
      .clk(w6),
      .rst(w16));

Clock_Divisior
     s2 (
      .clk(w5),
      .rst(w16),
      .out(w17));

PNU_DFF
     s3 (
      .Q(w8),
      .D(w9),
      .reset(w16),
      .clock(w17));

PNU_NOT
     s4 (
      .i1(w8),
      .o1(w9));

PNU_DFF
     s5 (
      .clock(w9),
      .Q(w10),
      .D(w11),
      .reset(w16));

PNU_NOT
     s6 (
      .i1(w10),
      .o1(w11));

PNU_DFF
     s7 (
      .clock(w11),
      .Q(w12),
      .D(w13),
      .reset(w16));

PNU_NOT
     s8 (
      .i1(w12),
      .o1(w13));

PNU_DFF
     s9 (
      .clock(w13),
      .Q(w14),
      .reset(w16),
      .D(w15));

PNU_NOT
     s10 (
      .i1(w14),
      .o1(w15));

endmodule

