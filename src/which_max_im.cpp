#include <Rcpp.h>
using namespace Rcpp;

//' Return (Row, Column) Index of (First) Maximum of an Integer Matrix
//' 
//' Written in C++, this function tends to run much faster than the equivalent 
//' (if maximum is unique) base R solution 
//' \code{which(x == max(x), arr.ind = TRUE)}.
//' 
//' For optimal speed, choose the version of this function that matches the 
//' class of your \code{x}:
//' 
//' \code{\link{which_max_nv}} for numeric vector. \cr
//' \code{\link{which_max_iv}} for integer vector. \cr
//' \code{\link{which_max_nm}} for numeric matrix. \cr
//' \code{\link{which_max_im}} for integer matrix.
//' 
//' @param x Integer matrix.
//' 
//' @return Integer vector.
//' 
//' @examples 
//' # which_max_im is typically much faster than 
//' which(x == max(x), arr.ind = TRUE)
//' x <- matrix(rpois(100, lambda = 15), ncol = 10)
//' all(which(x == max(x), arr.ind = TRUE) == which_max_im(x))
//' benchmark(which(x == max(x), arr.ind = TRUE), which_max_im(x), 
//'           replications = 5000)
//' 
//' @export
// [[Rcpp::export]]
IntegerVector which_max_im(IntegerMatrix x) {
  int ncols = x.ncol();
  int nrows = x.nrow();
  int currentx = x(0, 0);
  int maxx = currentx;
  IntegerVector loc(2);
  loc[0] = 0;
  loc[1] = 0;
  for (int a = 0; a < ncols; ++a) {
    for (int b = 0; b < nrows; ++b) {
      currentx = x(b, a);
      if (currentx > maxx) {
        maxx = currentx;
        loc[0] = b;
        loc[1] = a;
      }
    }
  }
  loc[0] += 1;
  loc[1] += 1;
  return(loc);
}