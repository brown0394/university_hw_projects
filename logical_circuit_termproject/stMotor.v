module stMotor(clk,rst,st);

input clk;
input rst;
output [3:0] st;

wire [3:0] b11;
wire  w16;
wire  w17;
wire  w18;
wire  w5;
wire  w6;

assign w6 = clk;
assign w5 = rst;
assign st = b11;

Clock_Divisior
     s1 (
      .out(w18),
      .rst(w5),
      .clk(w6));

stepMotor
     s0 (
      .cnt10(b11),
      .clk(w16),
      .rst(w5));

Clock_Divisior
     s10 (
      .out(w17),
      .clk(w18),
      .rst(w5));

Clock_Divisior
     s11 (
      .out(w16),
      .clk(w17),
      .rst(w5));

endmodule

