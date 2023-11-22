// SPDX-License-Identifier: MIT
/*
 *
 * This file is part of ruri, with ABSOLUTELY NO WARRANTY.
 *
 * MIT License
 *
 * Copyright (c) 2022-2023 Moe-hacker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 *
 */
// Do not format this.
// clang-format off
// The real value of them is not important here.
/*
 * Client: Nya?
 * Server: Nya!
 * Very cute, very moe...
 */
// From client.
#define FROM_CLIENT__TEST_MESSAGE            "Nya?"
#define FROM_CLIENT__KILL_A_CONTAINER        "0x01"
#define FROM_CLIENT__REGISTER_A_CONTAINER    "0x02"
#define FROM_CLIENT__KILL_DAEMON             "0x03"
#define FROM_CLIENT__GET_PS_INFO             "0x04"
#define FROM_CLIENT__IS_INIT_ACTIVE          "0x05"
#define FROM_CLIENT__INIT_COMMAND            "0x06"
#define FROM_CLIENT__END_OF_INIT_COMMAND     "0x07"
#define FROM_CLIENT__CAP_TO_DROP             "0x08"
#define FROM_CLIENT__END_OF_CAP_TO_DROP      "0x09"
#define FROM_CLIENT__MOUNTPOINT              "0x0a"
#define FROM_CLIENT__END_OF_MOUNTPOINT       "0x0b"
#define FROM_CLIENT__ENV                     "0x0c"
#define FROM_CLIENT__END_OF_ENV              "0x0d"
#define FROM_CLIENT__NO_NEW_PRIVS_TRUE       "0x0e"
#define FROM_CLIENT__NO_NEW_PRIVS_FALSE      "0x0f"
#define FROM_CLIENT__ENABLE_SECCOMP_TRUE     "0x10"
#define FROM_CLIENT__ENABLE_SECCOMP_FALSE    "0x11"
// From subprocess of daemon.
#define FROM_PTHREAD__INIT_PROCESS_DIED      "0x12"
#define FROM_PTHREAD__REGISTER_CONTAINER     "0x13"
#define FROM_PTHREAD__UNSHARE_CONTAINER_PID  "0x14"
#define FROM_PTHREAD__CAP_TO_DROP            "0x15"
#define FROM_PTHREAD__END_OF_CAP_TO_DROP     "0x16"
#define FROM_PTHREAD__MOUNTPOINT             "0x17"
#define FROM_PTHREAD__END_OF_MOUNTPOINT      "0x18"
#define FROM_PTHREAD__ENV                    "0x19"
#define FROM_PTHREAD__END_OF_ENV             "0x1a"
#define FROM_PTHREAD__NO_NEW_PRIVS_TRUE      "0x1b"
#define FROM_PTHREAD__NO_NEW_PRIVS_FALSE     "0x1c"
#define FROM_PTHREAD__ENABLE_SECCOMP_TRUE    "0x1d"
#define FROM_PTHREAD__ENABLE_SECCOMP_FALSE   "0x1e"
// From daemon.
#define FROM_DAEMON__TEST_MESSAGE            "Nya!"
#define FROM_DAEMON__UNSHARE_CONTAINER_PID   "0x1f"
#define FROM_DAEMON__CAP_TO_DROP             "0x20"
#define FROM_DAEMON__END_OF_CAP_TO_DROP      "0x21"
#define FROM_DAEMON__ENV                     "0x22"
#define FROM_DAEMON__END_OF_ENV              "0x23"
#define FROM_DAEMON__MOUNTPOINT              "0x24"
#define FROM_DAEMON__END_OF_MOUNTPOINT       "0x25"
#define FROM_DAEMON__CONTAINER_KILLED        "0x26"
#define FROM_DAEMON__CONTAINER_NOT_RUNNING   "0x27"
#define FROM_DAEMON__CONTAINER_IS_ACTIVE     "0x28"
#define FROM_DAEMON__CONTAINER_IS_NOT_ACTIVE "0x29"
#define FROM_DAEMON__INIT_IS_ACTIVE          "0x2a"
#define FROM_DAEMON__INIT_IS_NOT_ACTIVE      "0x2b"
#define FROM_DAEMON__END_OF_PS_INFO          "0x2c"
#define FROM_DAEMON__NO_NEW_PRIVS_TRUE       "0x2d"
#define FROM_DAEMON__NO_NEW_PRIVS_FALSE      "0x2e"
#define FROM_DAEMON__ENABLE_SECCOMP_TRUE     "0x2f"
#define FROM_DAEMON__ENABLE_SECCOMP_FALSE    "0x30"
// clang-format on
// Message buffer size.
#define MSG_BUF_SIZE (4096)