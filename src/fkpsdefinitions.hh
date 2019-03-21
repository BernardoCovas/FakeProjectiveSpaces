#ifndef _FKPSDEFINITIONS_H
#define _FKPSDEFINITIONS_H

#include <Eigen/Dense>

#include "fkpscdefs.h"

/*
    Fkps works with this mat type.
*/
typedef Eigen::Matrix<FkpsType_t, Eigen::Dynamic, Eigen::Dynamic> FkpsMat_t;


#endif /* _FKPSDEFINITIONS_H */
