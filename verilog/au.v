module au(
    input au_en,
    input [3:0] ac,
    input [7:0] a,b,
    output reg [7:0] t,
    output reg gf
);
always @(*) begin
    gf = 0;
    t = 8'HZZ;
    if(au_en) begin
        case(ac)
            4'b1000:
                t = a+b;
            4'b1001:begin
                t = b-a;
                gf = b>a?1'b1:1'b0;
            end
            4'b0100,
            4'b0101,
            4'b1101:
                t = a;
            default: ;
        endcase
    end
    else ;

end
endmodule