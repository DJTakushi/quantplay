enum cmd_k{
  buy =0,
  sell
};
struct order{
  cmd_k cmd_;
  double val_;
  order(cmd_k cmd, double val) : cmd_(cmd),val_(val){};
};