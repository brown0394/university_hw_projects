module bombRed(in,red);

input in;
output [3:0] red;

wire [3:0] b1;

assign red = b1;

assign b1[3] = in;
assign b1[2] = in;
assign b1[1] = in;
assign b1[0] = in;

endmodule

