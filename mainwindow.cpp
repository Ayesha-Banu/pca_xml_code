#include "mainwindow.h"





bool readSettingsXml(QIODevice &device, QMap<QString, QVariant> &map)
{

}

bool writeSettingsXml(QIODevice &device, const QMap<QString, QVariant> &map)
{
    XmlNode *root = new XmlNode(rootName);
qDebug() << "In write SettingS";

/************************************************************/
//step 1/2: process the structure of the settings map & the keys. the purpose
//of this step is to put all the keys of one category next to each other.
//but we do not sort within the category. in this step, we place our results
//from the QStringList of QMap.keys() into a tree-like structure
    foreach(const QString &unsplitKey, map.keys())
    {

        QStringList segs = unsplitKey.split("/", QString::SkipEmptyParts);
        QString val = map[unsplitKey].toString();

        XmlNode *cur = root;

        //for each segment of the current key, we loop through the branches of
        //our tree looking for appropriate branches/leaves. on the way down to
        //the specific leaf we want, we create & add nodes as needed.

        for(int i = 0; i < segs.length(); i++)
        {
            if(i == segs.length() - 1)
            {
                //the last segment is a leaf that wasn't previously found.
                //we don't keep the ref since it becomes a child of the parent
                new XmlNode(segs[i], val, cur);
            }
            else
            {
                //search for the node for the current segment. create it as a
                //child of the current node if it doesn't exist. then we use it
                //for the next iteration
                XmlNode *foundItem = 0;
                foreach(QObject *object, cur->children())
                {
                    XmlNode *child = (XmlNode*) object;
                    if(0 == QString::compare(child->tagName, segs[i], Qt::CaseInsensitive))
                    {
                        foundItem = child;
                        break;
                    }
                }

                if(!foundItem)
                    foundItem = new XmlNode(segs[i], QString(), cur);

                cur = foundItem;
            }
        }
    }

    QXmlStreamWriter xml(&device);
        xml.setAutoFormatting(true);
        xml.setAutoFormattingIndent(-1);
        xml.writeStartDocument();

        QList<XmlNode*> stack;
        stack << root;

        while(true)
        {
            //see step 1
            XmlNode *cur;
            while((cur = stack.takeLast()) == 0)
            {
                xml.writeEndElement();

                if(stack.isEmpty())
                {
                    xml.writeEndDocument();
                    delete root;
                    return true;
                }
            }

            //see step 2
            xml.writeStartElement(cur->tagName);
            stack << 0; // required to close text-only elements as well as for nodes with children to go back up a level when children are processed.

            //see step 3
            if(cur->children().size() == 0)
                xml.writeCharacters(cur->subtext);
            else
                for(int i = 0; i < cur->children().length(); i++)
                    stack << (XmlNode*) cur->children()[i];

        }

        //should *never* get here
        return false;
    }
