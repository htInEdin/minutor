#ifndef SEARCHBLOCKPLUGINWIDGET_H
#define SEARCHBLOCKPLUGINWIDGET_H

#include "searchplugininterface.h"
#include "searchtextwidget.h"

#include <QWidget>
#include <QLayout>
#include <set>


class SearchBlockPluginWidget : public QWidget, public SearchPluginI
{
  Q_OBJECT

 public:
  explicit SearchBlockPluginWidget(QWidget* parent = nullptr);
  ~SearchBlockPluginWidget();

  QWidget &getWidget() override;
  bool initSearch() override;
  SearchPluginI::ResultListT searchChunk(const Chunk &chunk) override;
  QString getSearchedFor() { return searchedFor; }

 private:
  QLayout* layout;

  SearchTextWidget* stw_blockId;
  SearchTextWidget* stw_blockName;

  QString searchedFor;

  std::set<quint32> m_searchForIds;
};

#endif // SEARCHBLOCKPLUGINWIDGET_H
