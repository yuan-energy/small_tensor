#pragma once
inline expr3<dat_t,d1,d2,d3,i1,i2,i3>&
operator=(expr3<dat_t,d1,d3,d2,i1,i3,i2> const& RHS_);

inline expr3<dat_t,d1,d2,d3,i1,i2,i3>&
operator=(expr3<dat_t,d2,d1,d3,i2,i1,i3> const& RHS_);

inline expr3<dat_t,d1,d2,d3,i1,i2,i3>&
operator=(expr3<dat_t,d2,d3,d1,i2,i3,i1> const& RHS_);

inline expr3<dat_t,d1,d2,d3,i1,i2,i3>&
operator=(expr3<dat_t,d3,d1,d2,i3,i1,i2> const& RHS_);

inline expr3<dat_t,d1,d2,d3,i1,i2,i3>&
operator=(expr3<dat_t,d3,d2,d1,i3,i2,i1> const& RHS_);

/*Done!*/