#include "root_iterator.h"

using namespace taco::ir;

namespace taco {
namespace storage {

RootIterator::RootIterator() {
}

Expr RootIterator::getPtrVar() const {
  return 0;
}

Expr RootIterator::getIdxVar() const {
  ierror << "The root iterator does not have an index var";
  return Expr();
}

ir::Expr RootIterator::getIteratorVar() const {
  ierror << "The root node does not have an iterator variable";
  return Expr();
}

Expr RootIterator::begin() const {
  ierror << "The root node does not have an iterator variable";
  return 0;
}

Expr RootIterator::end() const {
  ierror << "The root node does not have an iterator variable";
  return 1;
}

ir::Stmt RootIterator::initDerivedVars() const {
  return Stmt();
}

}}