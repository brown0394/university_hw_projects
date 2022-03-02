module ClockDivTen(clk,rst,out);

input clk;
input rst;
output out;

wire  w1;
wire  w3;
wire  w4;
wire  w5;
wire  w6;
wire  w7;

assign w1 = clk;
assign w7 = rst;
assign out = w3;

Clock_Divisior
     s0 (
      .clk(w1),
      .out(w6),
      .rst(w7));

Clock_Divisior
     s1 (
      .out(w5),
      .clk(w6),
      .rst(w7));

Clock_Divisior
     s2 (
      .out(w4),
      .clk(w5),
      .rst(w7));

Clock_Divisior
     s3 (
      .out(w3),
      .clk(w4),
      .rst(w7));

endmodule

