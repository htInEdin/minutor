#ifndef SEARCHPLUGININTERFACE_H
#define SEARCHPLUGININTERFACE_H

#include <vector>

class Chunk;

class QWidget;
class SearchResultItem;
class QString;

class SearchPluginI
{
 public:
  using ResultListT = std::vector<SearchResultItem>;


  virtual QWidget& getWidget() = 0;

  virtual bool initSearch() { return true; }

  virtual ResultListT searchChunk(const Chunk &chunk) = 0;

  virtual QString getSearchedFor() = 0;

  virtual ~SearchPluginI() {}
};

#endif // SEARCHPLUGININTERFACE_H
