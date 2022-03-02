module defuseGreen(in,green);

input in;
output [3:0] green;

wire [3:0] b1;

assign green = b1;

assign b1[3] = in;
assign b1[2] = in;
assign b1[1] = in;
assign b1[0] = in;

endmodule

