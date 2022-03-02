module OpSelector(in,p1);

input [2:0] in;
output [3:0] p1;

wire [3:0] b2;
wire [2:0] b1;
wire  w7;
wire  w8;
wire  b2_3;
wire  b2_2;
wire  b1_1_w12;
wire  b2_1;
wire  b1_2_w14;
wire  b1_0_w10;
wire  b2_0;

assign b1 = in;
assign p1 = b2;

assign b2[3] = b2_3;
assign b2[2] = b2_2;
assign b2[1] = b2_1;
assign b2[0] = b2_0;

assign b1_1_w12 = {b1[1]};
assign b1_2_w14 = {b1[2]};
assign b1_0_w10 = {b1[0]};

PNU_AND2
     s0 (
      .i1(w7),
      .i2(w8),
      .o1(b2_3));

PNU_AND2
     s1 (
      .i1(b1_2_w14),
      .i2(b1_0_w10),
      .o1(b2_0));

PNU_AND2
     s2 (
      .i1(b1_1_w12),
      .o1(b2_1),
      .i2(b1_0_w10));

PNU_NOT
     s3 (
      .o1(w7),
      .i1(b1_2_w14));

PNU_NOT
     s4 (
      .o1(w8),
      .i1(b1_1_w12));

PNU_NOT
     s5 (
      .o1(b2_2),
      .i1(b1_0_w10));

endmodule

