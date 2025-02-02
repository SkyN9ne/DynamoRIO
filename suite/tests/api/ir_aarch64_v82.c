/* **********************************************************
 * Copyright (c) 2015-2022 Google, Inc.  All rights reserved.
 * Copyright (c) 2022 ARM Limited. All rights reserved.
 * **********************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of ARM Limited nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL ARM LIMITED OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/* Define DR_FAST_IR to verify that everything compiles when we call the inline
 * versions of these routines.
 */
#ifndef STANDALONE_DECODER
#    define DR_FAST_IR 1
#endif

/* Uses the DR API, using DR as a standalone library, rather than
 * being a client library working with DR on a target program.
 */

#include "configure.h"
#include "dr_api.h"
#include "tools.h"

#include "ir_aarch64.h"

/*
 * FCVTAS
 */

TEST_INSTR(fcvtas_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTAS  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtas %q0 $0x01 -> %q0",
        "fcvtas %q10 $0x01 -> %q10",
        "fcvtas %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtas_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtas, instr, expected_0[i]))
            success = false;
    }

    /* FCVTAS  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtas %d0 $0x01 -> %d0",
        "fcvtas %d10 $0x01 -> %d10",
        "fcvtas %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtas_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtas, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtas_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTAS  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtas %h0 -> %w0",
        "fcvtas %h10 -> %w10",
        "fcvtas %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtas_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtas, instr, expected_0[i]))
            success = false;
    }

    /* FCVTAS  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtas %h0 -> %x0",
        "fcvtas %h10 -> %x10",
        "fcvtas %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtas_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtas, instr, expected_1[i]))
            success = false;
    }

    /* FCVTAS  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtas %h0 -> %h0",
        "fcvtas %h10 -> %h10",
        "fcvtas %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtas_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtas, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FCVTAU
 */

TEST_INSTR(fcvtau_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTAU  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtau %q0 $0x01 -> %q0",
        "fcvtau %q10 $0x01 -> %q10",
        "fcvtau %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtau_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtau, instr, expected_0[i]))
            success = false;
    }

    /* FCVTAU  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtau %d0 $0x01 -> %d0",
        "fcvtau %d10 $0x01 -> %d10",
        "fcvtau %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtau_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtau, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtau_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTAU  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtau %h0 -> %w0",
        "fcvtau %h10 -> %w10",
        "fcvtau %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtau_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtau, instr, expected_0[i]))
            success = false;
    }

    /* FCVTAU  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtau %h0 -> %x0",
        "fcvtau %h10 -> %x10",
        "fcvtau %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtau_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtau, instr, expected_1[i]))
            success = false;
    }

    /* FCVTAU  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtau %h0 -> %h0",
        "fcvtau %h10 -> %h10",
        "fcvtau %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtau_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtau, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FCVTMS
 */

TEST_INSTR(fcvtms_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTMS  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtms %q0 $0x01 -> %q0",
        "fcvtms %q10 $0x01 -> %q10",
        "fcvtms %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtms_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtms, instr, expected_0[i]))
            success = false;
    }

    /* FCVTMS  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtms %d0 $0x01 -> %d0",
        "fcvtms %d10 $0x01 -> %d10",
        "fcvtms %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtms_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtms, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtms_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTMS  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtms %h0 -> %w0",
        "fcvtms %h10 -> %w10",
        "fcvtms %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtms_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtms, instr, expected_0[i]))
            success = false;
    }

    /* FCVTMS  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtms %h0 -> %x0",
        "fcvtms %h10 -> %x10",
        "fcvtms %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtms_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtms, instr, expected_1[i]))
            success = false;
    }

    /* FCVTMS  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtms %h0 -> %h0",
        "fcvtms %h10 -> %h10",
        "fcvtms %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtms_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtms, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FCVTNS
 */

TEST_INSTR(fcvtns_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTNS  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtns %q0 $0x01 -> %q0",
        "fcvtns %q10 $0x01 -> %q10",
        "fcvtns %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtns_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtns, instr, expected_0[i]))
            success = false;
    }

    /* FCVTNS  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtns %d0 $0x01 -> %d0",
        "fcvtns %d10 $0x01 -> %d10",
        "fcvtns %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtns_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtns, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtns_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTNS  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtns %h0 -> %w0",
        "fcvtns %h10 -> %w10",
        "fcvtns %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtns_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtns, instr, expected_0[i]))
            success = false;
    }

    /* FCVTNS  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtns %h0 -> %x0",
        "fcvtns %h10 -> %x10",
        "fcvtns %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtns_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtns, instr, expected_1[i]))
            success = false;
    }

    /* FCVTNS  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtns %h0 -> %h0",
        "fcvtns %h10 -> %h10",
        "fcvtns %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtns_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtns, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FCVTPS
 */

TEST_INSTR(fcvtps_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTPS  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtps %q0 $0x01 -> %q0",
        "fcvtps %q10 $0x01 -> %q10",
        "fcvtps %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtps_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtps, instr, expected_0[i]))
            success = false;
    }

    /* FCVTPS  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtps %d0 $0x01 -> %d0",
        "fcvtps %d10 $0x01 -> %d10",
        "fcvtps %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtps_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtps, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtps_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTPS  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtps %h0 -> %w0",
        "fcvtps %h10 -> %w10",
        "fcvtps %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtps_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtps, instr, expected_0[i]))
            success = false;
    }

    /* FCVTPS  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtps %h0 -> %x0",
        "fcvtps %h10 -> %x10",
        "fcvtps %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtps_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtps, instr, expected_1[i]))
            success = false;
    }

    /* FCVTPS  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtps %h0 -> %h0",
        "fcvtps %h10 -> %h10",
        "fcvtps %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtps_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtps, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FCVTPU
 */

TEST_INSTR(fcvtpu_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTPU  <Vd>.8H, <Vn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "fcvtpu %q0 $0x01 -> %q0",
        "fcvtpu %q10 $0x01 -> %q10",
        "fcvtpu %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtpu_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtpu, instr, expected_0[i]))
            success = false;
    }

    /* FCVTPU  <Vd>.4H, <Vn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "fcvtpu %d0 $0x01 -> %d0",
        "fcvtpu %d10 $0x01 -> %d10",
        "fcvtpu %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtpu_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_fcvtpu, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(fcvtpu_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FCVTPU  <Wd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_W0, DR_REG_W10, DR_REG_W30 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "fcvtpu %h0 -> %w0",
        "fcvtpu %h10 -> %w10",
        "fcvtpu %h31 -> %w30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtpu_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtpu, instr, expected_0[i]))
            success = false;
    }

    /* FCVTPU  <Xd>, <Hn> */
    reg_id_t Rd_1[3] = { DR_REG_X0, DR_REG_X10, DR_REG_X30 };
    const char *expected_1[3] = {
        "fcvtpu %h0 -> %x0",
        "fcvtpu %h10 -> %x10",
        "fcvtpu %h31 -> %x30",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtpu_scalar(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtpu, instr, expected_1[i]))
            success = false;
    }

    /* FCVTPU  <Hd>, <Hn> */
    reg_id_t Rd_2[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_2[3] = {
        "fcvtpu %h0 -> %h0",
        "fcvtpu %h10 -> %h10",
        "fcvtpu %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fcvtpu_scalar(dc, opnd_create_reg(Rd_2[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_fcvtpu, instr, expected_2[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTA
 */

TEST_INSTR(frinta_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTA  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frinta %q0 $0x01 -> %q0",
        "frinta %q10 $0x01 -> %q10",
        "frinta %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinta_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frinta, instr, expected_0[i]))
            success = false;
    }

    /* FRINTA  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frinta %d0 $0x01 -> %d0",
        "frinta %d10 $0x01 -> %d10",
        "frinta %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinta_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frinta, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frinta_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTA  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frinta %h0 -> %h0",
        "frinta %h10 -> %h10",
        "frinta %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinta_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frinta, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTI
 */

TEST_INSTR(frinti_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTI  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frinti %q0 $0x01 -> %q0",
        "frinti %q10 $0x01 -> %q10",
        "frinti %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinti_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frinti, instr, expected_0[i]))
            success = false;
    }

    /* FRINTI  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frinti %d0 $0x01 -> %d0",
        "frinti %d10 $0x01 -> %d10",
        "frinti %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinti_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frinti, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frinti_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTI  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frinti %h0 -> %h0",
        "frinti %h10 -> %h10",
        "frinti %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frinti_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frinti, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTM
 */

TEST_INSTR(frintm_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTM  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frintm %q0 $0x01 -> %q0",
        "frintm %q10 $0x01 -> %q10",
        "frintm %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintm_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintm, instr, expected_0[i]))
            success = false;
    }

    /* FRINTM  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frintm %d0 $0x01 -> %d0",
        "frintm %d10 $0x01 -> %d10",
        "frintm %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintm_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintm, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frintm_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTM  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frintm %h0 -> %h0",
        "frintm %h10 -> %h10",
        "frintm %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintm_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frintm, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTN
 */

TEST_INSTR(frintn_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTN  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frintn %q0 $0x01 -> %q0",
        "frintn %q10 $0x01 -> %q10",
        "frintn %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintn_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintn, instr, expected_0[i]))
            success = false;
    }

    /* FRINTN  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frintn %d0 $0x01 -> %d0",
        "frintn %d10 $0x01 -> %d10",
        "frintn %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintn_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintn, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frintn_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTN  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frintn %h0 -> %h0",
        "frintn %h10 -> %h10",
        "frintn %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintn_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frintn, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTP
 */

TEST_INSTR(frintp_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTP  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frintp %q0 $0x01 -> %q0",
        "frintp %q10 $0x01 -> %q10",
        "frintp %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintp_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintp, instr, expected_0[i]))
            success = false;
    }

    /* FRINTP  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frintp %d0 $0x01 -> %d0",
        "frintp %d10 $0x01 -> %d10",
        "frintp %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintp_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintp, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frintp_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTP  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frintp %h0 -> %h0",
        "frintp %h10 -> %h10",
        "frintp %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintp_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frintp, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTX
 */

TEST_INSTR(frintx_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTX  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frintx %q0 $0x01 -> %q0",
        "frintx %q10 $0x01 -> %q10",
        "frintx %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintx_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintx, instr, expected_0[i]))
            success = false;
    }

    /* FRINTX  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frintx %d0 $0x01 -> %d0",
        "frintx %d10 $0x01 -> %d10",
        "frintx %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintx_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintx, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frintx_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTX  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frintx %h0 -> %h0",
        "frintx %h10 -> %h10",
        "frintx %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintx_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frintx, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FRINTZ
 */

TEST_INSTR(frintz_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTZ  <Hd>.8H, <Hn>.8H */
    opnd_t elsz;
    reg_id_t Rd_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_0[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_0[3] = {
        "frintz %q0 $0x01 -> %q0",
        "frintz %q10 $0x01 -> %q10",
        "frintz %q31 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintz_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintz, instr, expected_0[i]))
            success = false;
    }

    /* FRINTZ  <Hd>.4H, <Hn>.4H */
    reg_id_t Rd_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    elsz = OPND_CREATE_HALF();
    const char *expected_1[3] = {
        "frintz %d0 $0x01 -> %d0",
        "frintz %d10 $0x01 -> %d10",
        "frintz %d31 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintz_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]), elsz);
        if (!test_instr_encoding(dc, OP_frintz, instr, expected_1[i]))
            success = false;
    }

    return success;
}

TEST_INSTR(frintz_scalar)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FRINTZ  <Hd>, <Hn> */
    reg_id_t Rd_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    reg_id_t Rn_0[3] = { DR_REG_H0, DR_REG_H10, DR_REG_H31 };
    const char *expected_0[3] = {
        "frintz %h0 -> %h0",
        "frintz %h10 -> %h10",
        "frintz %h31 -> %h31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_frintz_scalar(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]));
        if (!test_instr_encoding(dc, OP_frintz, instr, expected_0[i]))
            success = false;
    }

    return success;
}

/*
 * FMLAL
 */

TEST_INSTR(fmlal_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FMLAL <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb> */

    /* FMLAL <Vd>.2S, <Vn>.2H, <Vm>.2H */
    reg_id_t Rd_0[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_0[3] = { DR_REG_S1, DR_REG_S11, DR_REG_S30 };
    reg_id_t Rm_0[3] = { DR_REG_S0, DR_REG_S10, DR_REG_S31 };
    const char *expected_0[3] = {
        "fmlal  %d0 %s1 %s0 $0x02 $0x01 -> %d0",
        "fmlal  %d10 %s11 %s10 $0x02 $0x01 -> %d10",
        "fmlal  %d31 %s30 %s31 $0x02 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr =
            INSTR_CREATE_fmlal_vector(dc, opnd_create_reg(Rd_0[i]),
                                      opnd_create_reg(Rn_0[i]), opnd_create_reg(Rm_0[i]));
        if (!test_instr_encoding(dc, OP_fmlal, instr, expected_0[i]))
            success = false;
    }

    /* FMLAL <Vd>.4S, <Vn>.4H, <Vm>.4H */
    reg_id_t Rd_1[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_1[3] = { DR_REG_D1, DR_REG_D11, DR_REG_D30 };
    reg_id_t Rm_1[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    const char *expected_1[3] = {
        "fmlal  %q0 %d1 %d0 $0x02 $0x01 -> %q0",
        "fmlal  %q10 %d11 %d10 $0x02 $0x01 -> %q10",
        "fmlal  %q31 %d30 %d31 $0x02 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr =
            INSTR_CREATE_fmlal_vector(dc, opnd_create_reg(Rd_1[i]),
                                      opnd_create_reg(Rn_1[i]), opnd_create_reg(Rm_1[i]));
        if (!test_instr_encoding(dc, OP_fmlal, instr, expected_1[i]))
            success = false;
    }

    return success;
}

/*
 * FMLAL2
 */

TEST_INSTR(fmlal2_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FMLAL2 <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb> */

    /* FMLAL2 <Vd>.2S, <Vn>.2H, <Vm>.2H */
    reg_id_t Rd_0[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_0[3] = { DR_REG_S1, DR_REG_S11, DR_REG_S30 };
    reg_id_t Rm_0[3] = { DR_REG_S2, DR_REG_S12, DR_REG_S29 };
    const char *expected_0[3] = {
        "fmlal2 %d0 %s1 %s2 $0x02 $0x01 -> %d0",
        "fmlal2 %d10 %s11 %s12 $0x02 $0x01 -> %d10",
        "fmlal2 %d31 %s30 %s29 $0x02 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fmlal2_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]),
                                           opnd_create_reg(Rm_0[i]));
        if (!test_instr_encoding(dc, OP_fmlal2, instr, expected_0[i]))
            success = false;
    }

    /* FMLAL2 <Vd>.4S, <Vn>.4H, <Vm>.4H */
    reg_id_t Rd_1[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_1[3] = { DR_REG_D1, DR_REG_D11, DR_REG_D30 };
    reg_id_t Rm_1[3] = { DR_REG_D2, DR_REG_D12, DR_REG_D29 };
    const char *expected_1[3] = {
        "fmlal2 %q0 %d1 %d2 $0x02 $0x01 -> %q0",
        "fmlal2 %q10 %d11 %d12 $0x02 $0x01 -> %q10",
        "fmlal2 %q31 %d30 %d29 $0x02 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fmlal2_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]),
                                           opnd_create_reg(Rm_1[i]));
        if (!test_instr_encoding(dc, OP_fmlal2, instr, expected_1[i]))
            success = false;
    }

    return success;
}

/*
 * FMLSL
 */

TEST_INSTR(fmlsl_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FMLSL <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb> */

    /* FMLSL <Vd>.2S, <Vn>.2H, <Vm>.2H */
    reg_id_t Rd_0[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_0[3] = { DR_REG_S1, DR_REG_S11, DR_REG_S30 };
    reg_id_t Rm_0[3] = { DR_REG_S2, DR_REG_S12, DR_REG_S29 };
    const char *expected_0[3] = {
        "fmlsl  %d0 %s1 %s2 $0x02 $0x01 -> %d0",
        "fmlsl  %d10 %s11 %s12 $0x02 $0x01 -> %d10",
        "fmlsl  %d31 %s30 %s29 $0x02 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr =
            INSTR_CREATE_fmlsl_vector(dc, opnd_create_reg(Rd_0[i]),
                                      opnd_create_reg(Rn_0[i]), opnd_create_reg(Rm_0[i]));
        if (!test_instr_encoding(dc, OP_fmlsl, instr, expected_0[i]))
            success = false;
    }

    /* FMLSL <Vd>.4S, <Vn>.4H, <Vm>.4H */
    reg_id_t Rd_1[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_1[3] = { DR_REG_D1, DR_REG_D11, DR_REG_D30 };
    reg_id_t Rm_1[3] = { DR_REG_D2, DR_REG_D12, DR_REG_D29 };
    const char *expected_1[3] = {
        "fmlsl  %q0 %d1 %d2 $0x02 $0x01 -> %q0",
        "fmlsl  %q10 %d11 %d12 $0x02 $0x01 -> %q10",
        "fmlsl  %q31 %d30 %d29 $0x02 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr =
            INSTR_CREATE_fmlsl_vector(dc, opnd_create_reg(Rd_1[i]),
                                      opnd_create_reg(Rn_1[i]), opnd_create_reg(Rm_1[i]));
        if (!test_instr_encoding(dc, OP_fmlsl, instr, expected_1[i]))
            success = false;
    }

    return success;
}

/*
 * FMLSL2
 */

TEST_INSTR(fmlsl2_vector)
{
    bool success = true;
    instr_t *instr;
    byte *pc;

    /* FMLSL2 <Vd>.<Ta>, <Vn>.<Tb>, <Vm>.<Tb> */

    /* FMLSL2 <Vd>.2S, <Vn>.2H, <Vm>.2H */
    reg_id_t Rd_0[3] = { DR_REG_D0, DR_REG_D10, DR_REG_D31 };
    reg_id_t Rn_0[3] = { DR_REG_S1, DR_REG_S11, DR_REG_S30 };
    reg_id_t Rm_0[3] = { DR_REG_S2, DR_REG_S12, DR_REG_S29 };
    const char *expected_0[3] = {
        "fmlsl2 %d0 %s1 %s2 $0x02 $0x01 -> %d0",
        "fmlsl2 %d10 %s11 %s12 $0x02 $0x01 -> %d10",
        "fmlsl2 %d31 %s30 %s29 $0x02 $0x01 -> %d31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fmlsl2_vector(dc, opnd_create_reg(Rd_0[i]),
                                           opnd_create_reg(Rn_0[i]),
                                           opnd_create_reg(Rm_0[i]));
        if (!test_instr_encoding(dc, OP_fmlsl2, instr, expected_0[i]))
            success = false;
    }

    /* FMLSL2 <Vd>.4S, <Vn>.4H, <Vm>.4H */
    reg_id_t Rd_1[3] = { DR_REG_Q0, DR_REG_Q10, DR_REG_Q31 };
    reg_id_t Rn_1[3] = { DR_REG_D1, DR_REG_D11, DR_REG_D30 };
    reg_id_t Rm_1[3] = { DR_REG_D2, DR_REG_D12, DR_REG_D29 };
    const char *expected_1[3] = {
        "fmlsl2 %q0 %d1 %d2 $0x02 $0x01 -> %q0",
        "fmlsl2 %q10 %d11 %d12 $0x02 $0x01 -> %q10",
        "fmlsl2 %q31 %d30 %d29 $0x02 $0x01 -> %q31",
    };
    for (int i = 0; i < 3; i++) {
        instr = INSTR_CREATE_fmlsl2_vector(dc, opnd_create_reg(Rd_1[i]),
                                           opnd_create_reg(Rn_1[i]),
                                           opnd_create_reg(Rm_1[i]));
        if (!test_instr_encoding(dc, OP_fmlsl2, instr, expected_1[i]))
            success = false;
    }

    return success;
}

int
main(int argc, char *argv[])
{
#ifdef STANDALONE_DECODER
    void *dcontext = GLOBAL_DCONTEXT;
#else
    void *dcontext = dr_standalone_init();
#endif
    bool result = true;
    bool test_result;

    RUN_INSTR_TEST(fcvtas_vector);
    RUN_INSTR_TEST(fcvtas_scalar);
    RUN_INSTR_TEST(fcvtau_vector);
    RUN_INSTR_TEST(fcvtau_scalar);
    RUN_INSTR_TEST(fcvtms_vector);
    RUN_INSTR_TEST(fcvtms_scalar);
    RUN_INSTR_TEST(fcvtns_vector);
    RUN_INSTR_TEST(fcvtns_scalar);
    RUN_INSTR_TEST(fcvtps_vector);
    RUN_INSTR_TEST(fcvtps_scalar);
    RUN_INSTR_TEST(fcvtpu_vector);
    RUN_INSTR_TEST(fcvtpu_scalar);

    RUN_INSTR_TEST(frinta_vector);
    RUN_INSTR_TEST(frinta_scalar);
    RUN_INSTR_TEST(frinti_vector);
    RUN_INSTR_TEST(frinti_scalar);
    RUN_INSTR_TEST(frintm_vector);
    RUN_INSTR_TEST(frintm_scalar);
    RUN_INSTR_TEST(frintn_vector);
    RUN_INSTR_TEST(frintn_scalar);
    RUN_INSTR_TEST(frintp_vector);
    RUN_INSTR_TEST(frintp_scalar);
    RUN_INSTR_TEST(frintx_vector);
    RUN_INSTR_TEST(frintx_scalar);
    RUN_INSTR_TEST(frintz_vector);
    RUN_INSTR_TEST(frintz_scalar);

    RUN_INSTR_TEST(fmlal_vector);
    RUN_INSTR_TEST(fmlal2_vector);
    RUN_INSTR_TEST(fmlsl_vector);
    RUN_INSTR_TEST(fmlsl2_vector);

    print("All v8.2 tests complete.\n");
#ifndef STANDALONE_DECODER
    dr_standalone_exit();
#endif
    if (result)
        return 0;
    return 1;
}
