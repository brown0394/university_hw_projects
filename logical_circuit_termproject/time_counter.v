module time_counter(clk,rst,ten,one,defused,deciSeg,hexSeg,timeMod,tensec,sec,LSB,bomb);

input clk;
input rst;
output ten;
output one;
input defused;
output [3:0] deciSeg;
output [2:0] hexSeg;
input timeMod;
output tensec;
output sec;
output LSB;
output bomb;

wire  w1;
wire  w31;
wire  w37;
wire  w35;
wire [3:0] b28;
wire  w32;
wire  w41;
wire [2:0] b26;
wire  w18;
wire  w20;
wire  w21;
wire  w22;
wire  w25;
wire  w24;
wire  w23;
wire  w26;
wire  w27;
wire  w19;
wire  w29;
wire  w28;

assign w19 = clk;
assign w28 = rst;
assign ten = w1;
assign one = w19;
assign w31 = defused;
assign deciSeg = b28;
assign hexSeg = b26;
assign w41 = timeMod;
assign tensec = w37;
assign sec = w32;
assign LSB = w35;
assign bomb = w26;

PNU_NOT
     s9 (
      .o1(w1),
      .i1(w19));

isFirst
     s34 (
      .out(w37),
      .clk(w18),
      .rst(w28));

time_part
     s22 (
      .LSB(w35),
      .decimal(b28),
      .seclock(w32),
      .clk(w20),
      .minten(w24),
      .zero(w27),
      .rst(w28));

time_part_two
     s15 (
      .timemod(w41),
      .hepta(b26),
      .heptazero(w22),
      .trizero(w25),
      .minten(w24),
      .rst(w28));

PNU_AND2
     s8 (
      .o1(w18),
      .i2(w24),
      .i1(w23));

PNU_NOT
     s7 (
      .i1(w31),
      .o1(w21));

PNU_AND2
     s10 (
      .o1(w20),
      .i1(w21),
      .i2(w19));

PNU_OR2
     s11 (
      .i1(w22),
      .i2(w25),
      .o1(w23));

PNU_AND2
     s13 (
      .i1(w23),
      .i2(w27),
      .o1(w29));

isFirst
     s12 (
      .out(w26),
      .clk(w29),
      .rst(w28));

endmodule

