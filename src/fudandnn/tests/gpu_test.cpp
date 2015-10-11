#include "boost/test/unit_test.hpp"

#include "viennacl/vector.hpp"
#include "viennacl/scalar.hpp"
#include "viennacl/linalg/inner_prod.hpp"
#include "viennacl/linalg/norm_1.hpp"
#include "viennacl/linalg/norm_2.hpp"
#include "viennacl/linalg/norm_inf.hpp"
#include "viennacl/tools/random.hpp"

#include <iostream>
#include <vector>

BOOST_AUTO_TEST_SUITE(GPUTest)

#ifdef FUDANDNN_GPU

BOOST_AUTO_TEST_CASE(DeviceTest) {
  
  std::cout << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << "               Device Info" << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << viennacl::ocl::current_device().info() << std::endl;
  
}

BOOST_AUTO_TEST_CASE(BLASTest) {
  //Change this type definition to double if your gpu supports that
  typedef float ScalarType;
  viennacl::tools::uniform_random_numbers<ScalarType> randomNumber;
  ScalarType s1 = ScalarType(3.1415926);
  ScalarType s2 = ScalarType(2.71763);
  ScalarType s3 = ScalarType(42.0);
  viennacl::scalar<ScalarType> vcl_s1;
  viennacl::scalar<ScalarType> vcl_s2 = ScalarType(1.0);
  viennacl::scalar<ScalarType> vcl_s3 = ScalarType(1.0);
  std::cout << "Copying a few scalars..." << std::endl;
  vcl_s1 = s1;
  s2 = vcl_s2;
  vcl_s3 = s3;
  std::cout << "Manipulating a few scalars..." << std::endl;
  std::cout << "operator +=" << std::endl;
  s1 += s2;
  vcl_s1 += vcl_s2;
  std::cout << "operator *=" << std::endl;
  s1 *= s2;
  vcl_s1 *= vcl_s2;
  std::cout << "operator -=" << std::endl;
  s1 -= s2;
  vcl_s1 -= vcl_s2;
  std::cout << "operator /=" << std::endl;
  s1 /= s2;
  vcl_s1 /= vcl_s2;
  std::cout << "operator +" << std::endl;
  s1 = s2 + s3;
  vcl_s1 = vcl_s2 + vcl_s3;
  std::cout << "multiple operators" << std::endl;
  s1 = s2 + s3 * s2 - s3 / s1;
  vcl_s1 = vcl_s2 + vcl_s3 * vcl_s2 - vcl_s3 / vcl_s1;
  std::cout << "mixed operations" << std::endl;
  vcl_s1 = s1 * vcl_s2 + s3 - vcl_s3;
  std::cout << "CPU scalar s3: " << s3 << std::endl;
  std::cout << "GPU scalar vcl_s3: " << vcl_s3 << std::endl;
  std::vector<ScalarType>      std_vec1(10);
  std::vector<ScalarType>      std_vec2(10);
  ScalarType                   plain_vec3[10];  //plain C array
  viennacl::vector<ScalarType> vcl_vec1(10);
  viennacl::vector<ScalarType> vcl_vec2(10);
  viennacl::vector<ScalarType> vcl_vec3(10);
  for (unsigned int i = 0; i < 10; ++i)
  {
    std_vec1[i] = randomNumber();
    vcl_vec2(i) = randomNumber();  //also works for GPU vectors, but is MUCH slower (approx. factor 10.000) than the CPU analogue
    plain_vec3[i] = randomNumber();
  }
  viennacl::copy(std_vec1.begin(), std_vec1.end(), vcl_vec1.begin()); //either the STL way
  viennacl::copy(vcl_vec2.begin(), vcl_vec2.end(), std_vec2.begin()); //either the STL way
  viennacl::copy(vcl_vec2, std_vec2);                                 //using the short hand notation for objects that provide .begin() and .end() members
  viennacl::copy(vcl_vec2.begin(), vcl_vec2.end(), plain_vec3);       //copy to plain C vector
  viennacl::copy(std_vec1.begin() + 4, std_vec1.begin() + 8, vcl_vec1.begin() + 4);   //cpu to gpu
  viennacl::copy(vcl_vec1.begin() + 4, vcl_vec1.begin() + 8, vcl_vec2.begin() + 1);   //gpu to gpu
  viennacl::copy(vcl_vec1.begin() + 4, vcl_vec1.begin() + 8, std_vec1.begin() + 1);   //gpu to cpu
  vcl_s1 = viennacl::linalg::inner_prod(vcl_vec1, vcl_vec2);
  s1 = viennacl::linalg::inner_prod(vcl_vec1, vcl_vec2);
  s2 = viennacl::linalg::inner_prod(std_vec1, std_vec2); //inner prod can also be used with std::vector (computations are carried out on CPU then)
  s1 = viennacl::linalg::norm_1(vcl_vec1);
  vcl_s2 = viennacl::linalg::norm_2(vcl_vec2);
  s3 = viennacl::linalg::norm_inf(vcl_vec3);
  viennacl::linalg::plane_rotation(vcl_vec1, vcl_vec2, 1.1f, 2.3f);
  //simple expression:
  vcl_vec1 = vcl_s1 * vcl_vec2 / vcl_s3;
  //more complicated expression:
  vcl_vec1 = vcl_vec2 / vcl_s3 + vcl_s2 * (vcl_vec1 - vcl_s2 * vcl_vec2);
  viennacl::swap(vcl_vec1, vcl_vec2);  //swaps all entries in memory
  viennacl::fast_swap(vcl_vec1, vcl_vec2); //swaps OpenCL memory handles only
  vcl_vec1.clear();
  vcl_vec2.clear();
  std::cout << "BLAS TEST COMPLETED SUCCESSFULLY" << std::endl;
  
}

#else
BOOST_AUTO_TEST_CASE(NOGPU) {
  std::cout << "GPU support isn't enabled" << std::endl;
}
#endif
  
BOOST_AUTO_TEST_SUITE_END()