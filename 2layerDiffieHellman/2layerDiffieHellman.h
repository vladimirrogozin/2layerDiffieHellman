/**
 * @file    2layerDiffieHellman.h
 * @brief   2layerDiffieHellman is a lib which implements advanced DiffieHellman's key exchange algorithm.
 *
 * Copyright (c) 2020-forever Vladimir Rogozin (vladimir20040609@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#ifndef RED_2LAYERDIFFIEHELLMAN_H
#define RED_2LAYERDIFFIEHELLMAN_H

// System libs.
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string>
#include <random>

// External libs.
#include <boost/multiprecision/cpp_int.hpp>

// RedLibrary.
#include "RedTypes.h"

// Version.
#define RED2LAYERDIFFIEHELLMAN_VERSION "2.0"

// Kits.
#define RED_2lDH_36m_AUTO  "auto mode enabled 36m"
#define RED_2lDH_64m_AUTO  "auto mode enabled 64m"
#define RED_2lDH_121m_AUTO "auto mode enabled 121m"
#define RED_2lDH_256m_AUTO "auto mode enabled 256m"
#define RED_2lDH_400m_AUTO "auto mode enabled 400m"

// Rand() setups.
#define RED_2lDH_RANDOM_A1_KEY_70m   8366
#define RED_2lDH_RANDOM_A1_KEY_105m  10246
#define RED_2lDH_RANDOM_A1_KEY_126m  11224
#define RED_2lDH_RANDOM_A1_KEY_238m  15427
#define RED_2lDH_RANDOM_A1_KEY_336m  18330

namespace Red {
    /// Creating a template for integers, because we need it to be cross-typed.
    template<class INT_SIZE>
    class TwoLayerDiffieHellman {
        private:
            //
            // Variables.
            //

            /// x = G**a mod P

            /// Local vars.
            const INT_SIZE m_G    = 2, // Base for part 1.
                           m_Pp1  = 2; // P num for part 1.

            unsigned short int m_base; // Base for part 2.

            /// User's vars.
            INT_SIZE *m_P,   // Prime num for part 2.
                     *m_a1, // Secret num for part 1.
                     *m_a2; // Secret num for part 2.


            ///
            /// Different modes.
            ///

            std::string m_mode; // Mode of secret key usage.

            /// 36m kit.
            const unsigned long long int m_range_36m  = 6000;

            /// 64m kit.
            const unsigned long long int m_range_64m  = 8000;

            /// 121m kit.
            const unsigned long long int m_range_121m  = 11000;

            /// 256m kit.
            const unsigned long long int m_range_256m  = 16000;

            /// 400m kit.
            const unsigned long long int m_range_400m  = 20000;


            //
            // Private functions.
            //

            /**
             * @brief power
             *
             * Serves to generate a key using a, b.
             * Uses only in part 1.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * power(const INT_SIZE *a, const INT_SIZE *b, const INT_SIZE *P) const {
                if (*b == 1) {
                    INT_SIZE *res = new INT_SIZE;
                    *res = *a;
                    return res;

                } else {
                    // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                    // So, let's do that!

                    /// Need to get cpp_int version of base.
                    boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                    /// And ui version of our exponent.
                    Red::uint_t b_int = 0;

                    {
                        std::stringstream ss;
                        ss << *b;
                        ss >> b_int;
                    }

                    /// Let's get exponented 'a'...
                    boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                    /// Now we need cpp_int version of 'P'.
                    boost::multiprecision::cpp_int p_c = 0;

                    {
                        std::stringstream ss;
                        ss << *P;
                        ss >> p_c;
                    }

                    /// Moded expenented 'a' is needed...
                    boost::multiprecision::cpp_int abp = ab % p_c;

                    /// Now we just need to convert it to the type we need.
                    INT_SIZE *res = new INT_SIZE;

                    {
                        std::stringstream ss;
                        ss << abp;
                        ss >> *res;
                    }

                    /// Yay, we finished this.
                    return res;
                }
            }

            /**
             * @brief powerUSI
             *
             * Serves to generate a key using a, b, P.
             * Uses only in part 1.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * powerUSI(const unsigned short int *a, const INT_SIZE *b, const INT_SIZE *P) const {
                if (*b == 1) {
                    INT_SIZE *res = new INT_SIZE;
                    *res = *a;
                    return res;

                } else {
                    // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                    // So, let's do that!

                    /// Need to get cpp_int version of base.
                    boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                    /// And ui version of our exponent.
                    Red::uint_t b_int = 0;

                    {
                        std::stringstream ss;
                        ss << *b;
                        ss >> b_int;
                    }

                    /// Let's get exponented 'a'...
                    boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                    /// Now we need cpp_int version of 'P'.
                    boost::multiprecision::cpp_int p_c = 0;

                    {
                        std::stringstream ss;
                        ss << *P;
                        ss >> p_c;
                    }

                    /// Moded expenented 'a' is needed...
                    boost::multiprecision::cpp_int abp = ab % p_c;

                    /// Now we just need to convert it to the type we need.
                    INT_SIZE *res = new INT_SIZE;

                    {
                        std::stringstream ss;
                        ss << abp;
                        ss >> *res;
                    }

                    /// Yay, we finished this.
                    return res;
                }
            }

            /**
             * @brief power_2_pub
             *
             * Serves to generate a key using a, b, P.
             * Used only for getting a public value in part 2.
             *
             * @param a Number which we will modificate.
             * @param b Chosen private key.
             * @param P Result number.
             *
             * @return Generated key.
             */
            inline INT_SIZE * power_2_pub(const unsigned short int *a, const unsigned long long int& b, const INT_SIZE *P) const {
                // Unfortunately we have to write a lot here, because there is no a good way to write it shorter.
                // So, let's do that (again)!

                /// Need to get cpp_int version of base.
                boost::multiprecision::cpp_int a_c = boost::multiprecision::cpp_int(*a);

                /// And ui version of a random exponent.
                srand(time(0));
                Red::uint_t b_int;

                *m_a2 = (unsigned int) rand() % b;

                if ((b - *m_a2) >= 2) {
                    *m_a2 += 2;
                }

                {
                   std::stringstream ss;
                   ss << *m_a2;
                   ss >> b_int;
                }

                /// Let's get exponented 'a'...
                boost::multiprecision::cpp_int ab = boost::multiprecision::pow(a_c, b_int);

                /// Now we need cpp_int version of 'P'.
                boost::multiprecision::cpp_int p_c = 0;

                {
                    std::stringstream ss;
                    ss << *P;
                    ss >> p_c;
                }

                /// Moded expenented 'a' is needed...
                boost::multiprecision::cpp_int abp = ab % p_c;

                /// Now we just need to convert it to the type we need.
                INT_SIZE *res = new INT_SIZE;

                {
                    std::stringstream ss;
                    ss << abp;
                    ss >> *res;
                }

                /// Yay, we finished this.
                return res;
            }

        public:
            /**
             * @brief TwoLayerDiffieHellman
             *
             * GeneratedKey = G**a mod P
             *
             * Where,
             * @param ModificatedNum P number.
             * @param SecretNum1 Secret number 1.
             * @param SecretNum2 Secret number 2.
             * @param Mode Mode of secret key usage.
             */
            TwoLayerDiffieHellman(INT_SIZE *ModificatedNum = 0,
                                  INT_SIZE *SecretNum1 = 0,
                                  INT_SIZE *SecretNum2 = 0,
                                  std::string_view Mode = "manual")
                : m_P(ModificatedNum), m_a1(SecretNum1), m_a2(SecretNum2), m_mode(Mode) {}

            /**
             * @brief Set
             *
             * GeneratedKey = G**a mod P
             *
             * Where,
             * @param ModificatedNum P number.
             * @param SecretNum1 Secret number 1.
             * @param SecretNum2 Secret number 2.
             * @param Mode Mode of secret key usage.
             */
            void Set(INT_SIZE *ModificatedNum,
                     INT_SIZE *SecretNum1,
                     INT_SIZE *SecretNum2,
                     std::string_view Mode = "manual") {

                this->m_P    = ModificatedNum;
                this->m_a1   = SecretNum1;
                this->m_a2   = SecretNum2;
                this->m_mode = Mode;

                // m_base clears itself when calculates.
            }

            /**
             * @brief Part1_GetPublicValue
             *
             * Serves to calculate a value for partner.
             *
             * @return Value for public exchange.
             */
            INT_SIZE * Part1_GetPublicValue() const {
                return power(&this->m_G, this->m_a1, this->m_P);
            }

            /**
             * @brief Part1_GetSymmetricBaseNum
             *
             * Serves to to calculate symmetric value.
             *
             * @param x Partner's key, which we got after exchange part.
             */
            void Part1_GetSymmetricBaseNum(INT_SIZE *x) {
                INT_SIZE *u;

                u = power(x, this->m_a1, &this->m_Pp1);

                /// Getting a base num.
                if (*u == 0) {
                    m_base = 2;

                } else if (*u == 1) {
                    m_base = 3;

                } else {
                    throw "[\033[91m2layerDiffieHellman\033[0m]: hello from here!";
                }
            }

            /**
             * @brief Part2_GetPublicValue
             *
             * Serves to calculate a value for partner.
             *
             * @return Value for public exchange.
             */
            INT_SIZE * Part2_GetPublicValue() const {
                if (m_mode == "manual") {
                    return powerUSI(&this->m_base, this->m_a2, this->m_P); // unsigned short int edition.

                } else { // auto mode enabled && wrong usage.
                    if (m_mode == "auto mode enabled 36m") {
                        return power_2_pub(&this->m_base, this->m_range_36m, this->m_P);

                    } else if (m_mode == "auto mode enabled 64m") {
                        return power_2_pub(&this->m_base, this->m_range_64m, this->m_P);

                    } else if (m_mode == "auto mode enabled 121m") {
                        return power_2_pub(&this->m_base, this->m_range_121m, this->m_P);

                    } else if (m_mode == "auto mode enabled 256m") {
                        return power_2_pub(&this->m_base, this->m_range_256m, this->m_P);

                    } else if (m_mode == "auto mode enabled 400m") {
                        return power_2_pub(&this->m_base, this->m_range_400m, this->m_P);

                    } else {
                        return power_2_pub(&this->m_base, this->m_range_64m, this->m_P);
                    }
                }
            }

            /**
             * @brief Part2_GetSymmetricSecret
             *
             * Serves to to calculate the final value.
             *
             * @param x Partner's key, which we got after exchange operation.
             *
             * @return Final num.
             */
            INT_SIZE * Part2_GetSymmetricSecret(INT_SIZE *x) const {
                return power(x, this->m_a2, this->m_P);
            }

            // Base dtor.
            ~TwoLayerDiffieHellman() {}
    };
}

#endif // RED_2LAYERDIFFIEHELLMAN_H
