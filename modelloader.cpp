#include "modelloader.h"

ModelLoader::ModelLoader()
{
  materialDefault.Ambient = QVector3D(0.1f, 0.05f, 0.0f);
     materialDefault.Diffuse = QVector3D(.9f, .6f, .2f);
     materialDefault.Specular = QVector3D(.2f, .2f, .2f);
     materialDefault.Shininess = 50.0f;
}

ModelLoader::~ModelLoader()
{

}

bool ModelLoader::load(QString pathToFile)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(pathToFile.toStdString(),
            aiProcess_GenSmoothNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType
            );

    if (!scene){
        qDebug() << "Error loading file: (assimp:) " << importer.GetErrorString();
        return false;
    }

    if (scene->HasMaterials())
        {
            for (unsigned int ii = 0; ii < scene->mNumMaterials; ++ii)
            {
                QSharedPointer<MaterialInfo> mater = processMaterial(scene->mMaterials[ii]);
                m_materials.push_back(mater);
            }
        }
    if (scene->HasMeshes())
        {
            for (unsigned int ii = 0; ii < scene->mNumMeshes; ++ii)
            {
                m_meshes.push_back(processMesh(scene->mMeshes[ii]));
            }
        }
        else
        {
            qDebug() << "Error: No meshes found";
            return false;
        }
      if (scene->mRootNode != NULL)
        {
            Node *rootNode = new Node;
            processNode(scene, scene->mRootNode, 0, *rootNode);
            m_rootNode.reset(rootNode);
        }
        else
        {
            qDebug() << "Error loading model";
            return false;
        }
        for(int i =0; i <m_meshes.size();i++)
        {
          qDebug() << m_meshes[i]->indexCount<< m_meshes[i]->indexOffset;
        }
}

void ModelLoader::getBufferData(QVector<QVector3D> **vertices, QVector<QVector3D> **normals, QVector<unsigned int> **indices)
{
  *vertices=&m_vertices;
  *normals=&m_normals;
  *indices=&m_indices;
}

GLuint ModelLoader::getGlList()
{
  GLuint modelList;
  modelList = glGenLists(1);
  glNewList (modelList, GL_COMPILE);
  qDebug() << "prima di render";
  renderModel(m_rootNode.data(),QMatrix4x4());
  qDebug() << "dopo di render";
  glEndList();
  return modelList;
}

void ModelLoader::renderModel(const Node* node,QMatrix4x4 objectMatrix)
{
  objectMatrix *= node->transformation;
  QVector<QSharedPointer<Mesh> > immmeshes =node->meshes;
//  qDebug() << node->name << immmeshes.size();
//  for (int imm = 0; imm<immmeshes.size(); ++imm){
//    qDebug() <<"INDICI     " <<immmeshes[imm]->indexOffset<< immmeshes[imm]->indexCount
//    <<m_normals.size()<< m_vertices.size();
//}
  for (int imm = 0; imm<immmeshes.size(); ++imm)
  {
//      qDebug() << "DENTRO for" <<node->name<<immmeshes[imm]->material->Name;

      if (node->meshes[imm]->material->Name == QString("DefaultMaterial"))
          setMaterialUniforms(materialDefault);
      else
          setMaterialUniforms(*node->meshes[imm]->material);

//      qDebug() << node->meshes[imm]->indexOffset;


      glBegin(GL_POLYGON);
        for(int i = immmeshes[imm]->indexOffset; i <immmeshes[imm]->indexCount;i++){
            qDebug() << m_normals[i].x()<<m_normals[i].y()<<m_normals[i].z();
            glNormal3f (m_normals[i].x(),m_normals[i].y(),m_normals[i].z());
            qDebug() << m_vertices[i].x()<<m_vertices[i].y()<<m_vertices[i].z();
            glVertex3f(m_vertices[i].x(),m_vertices[i].y(),m_vertices[i].z());

        }
      glEnd();
  }

  QVector<Node> innnodes=node->nodes;
//  qDebug() << node->name << "nodi figli"<< innnodes.size();
  for (int inn = 0; inn < innnodes.size(); ++inn)
      renderModel(&node->nodes[inn], objectMatrix);
}

QSharedPointer<MaterialInfo> ModelLoader::processMaterial(aiMaterial *material)
{
    QSharedPointer<MaterialInfo> mater(new MaterialInfo);

       aiString mname;
       material->Get(AI_MATKEY_NAME, mname);
       if (mname.length > 0)
           mater->Name = mname.C_Str();

       int shadingModel;
       material->Get(AI_MATKEY_SHADING_MODEL, shadingModel);

       if (shadingModel != aiShadingMode_Phong && shadingModel != aiShadingMode_Gouraud)
       {
           qDebug() << "This mesh's shading model is not implemented in this loader, setting to default material";
           mater->Name = "DefaultMaterial";
       }
       else
       {
               aiColor3D dif(0.f,0.f,0.f);
               aiColor3D amb(0.f,0.f,0.f);
               aiColor3D spec(0.f,0.f,0.f);
               float shine = 0.0;

               material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
               material->Get(AI_MATKEY_COLOR_DIFFUSE, dif);
               material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
               material->Get(AI_MATKEY_SHININESS, shine);

               mater->Ambient = QVector3D(amb.r, amb.g, amb.b);
               mater->Diffuse = QVector3D(dif.r, dif.g, dif.b);
               mater->Specular = QVector3D(spec.r, spec.g, spec.b);
               mater->Shininess = shine;

               mater->Ambient *= .2;
               if (mater->Shininess == 0.0)
                   mater->Shininess = 30;
           }

           return mater;
}

QSharedPointer<Mesh> ModelLoader::processMesh(aiMesh *mesh)
{
  QSharedPointer<Mesh> newMesh(new Mesh);
      newMesh->name = mesh->mName.length != 0 ? mesh->mName.C_Str() : "";
      newMesh->indexOffset = m_indices.size();
      unsigned int indexCountBefore = m_indices.size();
      int vertindexoffset = m_vertices.size();

      // Get Vertices
      if (mesh->mNumVertices > 0)
      {
          for (uint ii = 0; ii < mesh->mNumVertices; ++ii)
          {
              aiVector3D &vec = mesh->mVertices[ii];
              QVector3D vertex(vec.x,vec.y,vec.z);
              m_vertices.push_back(vertex);
          }
      }

      // Get Normals
      if (mesh->HasNormals())
      {
          for (uint ii = 0; ii < mesh->mNumVertices; ++ii)
          {
              aiVector3D &vec = mesh->mNormals[ii];
              QVector3D normal(vec.x,vec.y,vec.z);
              m_normals.push_back(normal);
          };
      }

      // Get mesh indexes
      for (uint t = 0; t < mesh->mNumFaces; ++t)
      {
          aiFace* face = &mesh->mFaces[t];
          if (face->mNumIndices != 3)
          {
              qDebug() << "Warning: Mesh face with not exactly 3 indices, ignoring this primitive.";
              continue;
          }

          m_indices.push_back(face->mIndices[0]+vertindexoffset);
      }

      newMesh->indexCount = m_indices.size() - indexCountBefore;
      newMesh->material = m_materials.at(mesh->mMaterialIndex);

      return newMesh;
}

void ModelLoader::processNode(const aiScene *scene, aiNode *node, Node *parentNode, Node &newNode)
{
  newNode.name = node->mName.length != 0 ? node->mName.C_Str() : "";

      newNode.transformation = QMatrix4x4(node->mTransformation[0]);

      newNode.meshes.resize(node->mNumMeshes);
      for (uint imesh = 0; imesh < node->mNumMeshes; ++imesh)
      {
          QSharedPointer<Mesh> mesh = m_meshes[node->mMeshes[imesh]];
          newNode.meshes[imesh] = mesh;
      }

      for (uint ich = 0; ich < node->mNumChildren; ++ich)
      {
          newNode.nodes.push_back(Node());
          processNode(scene, node->mChildren[ich], parentNode, newNode.nodes[ich]);
      }
}

void ModelLoader::transformToUnitCoordinates()
{

}

void ModelLoader::findObjectDimensions(Node *node, QMatrix4x4 transformation, QVector3D &minDimension, QVector3D &maxDimension)
{

}

void ModelLoader::setMaterialUniforms(MaterialInfo &material)
{
  GLfloat ambient[3] ={material.Ambient.x(),material.Ambient.y(),material.Ambient.z()};
  GLfloat diffuse[3] ={material.Diffuse.x(),material.Diffuse.y(),material.Diffuse.z()};
  GLfloat specular[3]={material.Specular.x(),material.Specular.y(),material.Specular.z()};

  glMaterialfv(GL_FRONT, GL_SPECULAR, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material.Shininess);



}

