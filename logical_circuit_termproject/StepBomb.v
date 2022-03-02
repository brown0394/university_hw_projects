module StepBomb(clk,rst,st);

input clk;
input rst;
output [3:0] st;

wire [3:0] b11;
wire  w18;
wire  w6;
wire  w7;
wire  w8;
wire  w9;
wire  w10;
wire  w14;
wire  w11;
wire  w13;
wire  w12;

assign w13 = clk;
assign w12 = rst;
assign st = b11;

Clock_Divisior
     s1 (
      .out(w18),
      .clk(w13),
      .rst(w12));

stepMotor
     s0 (
      .cnt10(b11),
      .clk(w11),
      .rst(w12));

Clock_Divisior
     s10 (
      .clk(w18),
      .out(w14),
      .rst(w12));

PNU_DFF
     s3 (
      .Q(w6),
      .D(w7),
      .clock(w14),
      .reset(w12));

PNU_NOT
     s4 (
      .i1(w6),
      .o1(w7));

PNU_DFF
     s2 (
      .clock(w7),
      .Q(w8),
      .D(w9),
      .reset(w12));

PNU_NOT
     s6 (
      .i1(w8),
      .o1(w9));

PNU_DFF
     s7 (
      .clock(w9),
      .Q(w10),
      .D(w11),
      .reset(w12));

PNU_NOT
     s5 (
      .i1(w10),
      .o1(w11));

endmodule

