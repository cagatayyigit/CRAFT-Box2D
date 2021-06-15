# CRAFT-Box2D

The simulator that we used to render 2D physics simulations which output simulation data used to generate questions. You can go to [here](https://github.com/hucvl/craft) for detailed explanations.

**CRAFT: A Benchmark for Causal Reasoning About Forces and inTeractions**
<br>Tayfun Ates*, M. Samil Atesoglu*, Cagatay Yigit*, Ilker Kesen, Mert Kobas, Erkut Erdem, Aykut Erdem, Tilbe Goksun, Deniz Yuret
<br>*NeurIPS 2021 Submission, Datasets and Benchmarks Track*

[OpenReview Preprint](https://openreview.net/pdf?id=GVe2IvtZtVY), [Project Website](https://sites.google.com/view/craft-benchmark) 

The dataset is available on [Zenodo](https://zenodo.org/record/4904783).
___

Box2D provides 2-dimensional physics engine for our simulations. To draw simulated objects, we extended it and add the following classes. Some of them are derived from their counterparts in box2d.

- b2VisBody
- b2VisWorld
- b2VisTexure
- b2VisPolygonShape

b2VisBody holds color and/or texture information for box2d bodies to be rendered in our own renderer. b2VisWorld is the corresponding class which knows that the attached bodies has the type of b2VisBody.

For material textures (if used), b2VisTexture depend on [libpng](http://www.libpng.org/) to load texture from file. Texture coordinates of polygons can be obtained from the interface provided in b2VisPolygonShape.

b2VisWorld has the interface to reach the renderer. By the help of this interface, you can have renderer to output rendered images to output file for each step required by the simulation.

To be able to import the simulation data from json files or to export the simulation data to json files (settings, objects, scene information etc.), following repository is used for serialization/deserialization:

[nlohmann's json serialization/deserialization library](https://github.com/nlohmann/json)

It can be installed via brew as stated in the documentation of the library if you are using OSX. Please refer readme of the repository for other operating systems.

To output video ffmpeg is also required.
