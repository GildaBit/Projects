op_codes = {
    'add': '000000',
    'sub': '000000',
    'and': '000000',
    'or': '000000',
    'slt': '000000',
    'lw': '100011',
    'sw': '101011',
    'beq': '000100',
    'bne': '000101'
}

func_codes = {
    'add': '100000',
    'sub': '100010',
    'and': '100100',
    'or': '100101',
    'slt': '101010'
}

registers = {
    '$zero': '00000',
    '$t1': '01001',
    '$t2': '01010',
    '$t3': '01011',
    '$t4': '01100',
    '$t5': '01101',
    '$t6': '01110',
    '$t7': '01111',
    '$s0': '10000',
    '$s1': '10001',
    '$s2': '10010',
    '$s3': '10011',
    '$s4': '10100',
    '$s5': '10101',
    '$s6': '10110',
    '$s7': '10111'
}

shift_logic_amount = "00000"

def assembleFile(bin_file_path, asm_file_path ,mhc_file_path):
    asm_file = open(asm_file_path, 'r')
    bin_file = open(bin_file_path, 'w')
    mhc_file = open(mhc_file_path, 'wb')

    for asm_line in asm_file.readlines():
        machine_code = assembleAsm(asm_line)
        bin_file.write(machine_code)

        machine_code_num = int(machine_code, 2)
        val = machine_code_num.to_bytes(4, byteorder='big')
        mhc_file.write(val)

def assembleAsm(asm_line):
    asm_line = asm_line.split("#")[0].strip()

    if not asm_line:
        return ""
    
    parts = asm_line.split(" ")

    op_code = parts[0]

    if op_code in func_codes:
        op_code, rd, rs, rt = parts
        rd, rs, rt = rd.strip(","), rs.strip(","), rt.strip(",")
        op_code_bin, func_code_bin, rd_bin, rs_bin, rt_bin = op_codes[op_code], func_codes[op_code], registers[rd], registers[rs], registers[rt]
        return op_code_bin + rd_bin + rs_bin + rt_bin + shift_logic_amount + func_code_bin 
    elif op_code in ['lw', 'sw', 'beq', 'bnq']:
        if op_code == 'lw' or op_code == 'sw':
            rt_bin = registers[parts[1].strip(',')]
            offset, rs = parts[2].strip(")").split("(")
            rs_bin = registers[rs]
            offset_bin = bin(int(offset)).replace("0b", "").zfill(16)
            op_code_bin = op_codes[op_code]
            return op_code_bin + rs_bin + rt_bin + offset_bin
        elif op_code == 'beq' or op_code == 'bne':
            rs_bin = registers[parts[1].strip(',')]
            rt_bin = registers[parts[2].strip(',')]
            offset = parts[3].strip(",")
            offset_bin = bin(int(offset)).replace("0b", "").zfill(16)
            op_code_bin = op_codes[op_code]
            return op_code_bin + rs_bin + rt_bin + offset_bin

assembleFile("C:\\Users\\bitto\\OneDrive\\Desktop\\REPOSITORY\\CS240\\assignment_3\\program.bin", "C:\\Users\\bitto\\OneDrive\\Desktop\\REPOSITORY\\CS240\\assignment_3\\program.asm", "C:\\Users\\bitto\\OneDrive\\Desktop\\REPOSITORY\\CS240\\assignment_3\\program.mhc")